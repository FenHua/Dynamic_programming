/*Skip_Knapsack.cpp : 定义控制台应用程序的入口点。
由m(i,j)的递归式容易证明，在一般情况下，对每一个确定的i(1≤i≤n)，函数m(i,j)是关于变量j的阶梯状单调不减函数。
跳跃点是这一类函数的描述特征。在一般情况下，函数m(i,j)由其全部跳跃点唯一确定。
函数m(i,j)是由函数m(i+1,j)与函数m(i+1,j-wi)+vi作max运算得到的。因此，函数m(i,j)的全部跳跃点包含于
函数m(i+1，j)的跳跃点集p[i+1]与函数m(i+1，j-wi)+vi的跳跃点集q[i+1]的并集中。易知，(s,t)∈q[i+1]当且
仅当wi<=s<=c且(s-wi,t-vi)∈p[i+1]。因此，容易由p[i+1]确定跳跃点集q[i+1]如下：
q[i+1]=p[i+1]⊕(wi,vi)={(j+wi,m(i,j)+vi)|(j,m(i,j))∈p[i+1]}
另一方面，设(a，b)和(c，d)是p[i+1]∪q[i+1]中的2个跳跃点，则当c>=a且d<b时，(c，d)
受控于(a，b)，从而(c，d)不是p[i]中的跳跃点。除受控跳跃点外，p[i+1]∪q[i+1]中的其他跳跃点均
为p[i]中的跳跃点。由此可见，在递归地由表p[i+1]计算表p[i]时，可先由p[i+1]计算出q[i+1]，然后合
并表p[i+1]和表q[i+1]，并清除其中的受控跳跃点得到表p[i]。
*/

#include "stdafx.h"
#include"iostream"
using namespace std;

const int N = 4;
template<class type>int Knapsack(int n, type c,type v[], type w[], int**p, int x[]);
template<class type>void Traceback(int n, type w[], type v[], type**p, int *head, int x[]);

int main()
{
	int c = 8;
	int v[] = { 0, 2, 1, 4, 3 }, w[] = { 0, 1, 4, 2, 3 };//下标从1开始  
	int x[N + 1];

	int **p = new int *[50];
	for (int i = 0; i<50; i++)
	{
		p[i] = new int[2];
	}

	cout << "待装物品重量分别为：" << endl;
	for (int i = 1; i <= N; i++)
	{
		cout << w[i] << " ";
	}
	cout << endl;

	cout << "待装物品价值分别为：" << endl;
	for (int i = 1; i <= N; i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	cout << "背包能装的最大价值为：" << Knapsack(N, c, v, w, p, x) << endl;

	cout << "背包装下的物品编号为：" << endl;
	for (int i = 1; i <= N; i++)
	{
		if (x[i] == 1)
		{
			cout << i << " ";
		}
	}
	cout << endl;

	for (int i = 0; i<50; i++)
	{
		delete p[i];
	}

	delete[] p;
	return 0;
}

template<class type>int Knapsack(int n, type c, type v[], type w[], int **p, int x[])
{
	int *head = new int[n + 2];
	head[n + 1] = 0;
	p[0][0] = 0;//p[][0]存储物品的重量
	p[0][1] = 0;//p[][1]存储物品的价值，物品n的跳跃点(0,0)
	//left指向p[i+1]的第一个跳跃点，right指向最后一个
	int left = 0, right = 0, next = 1;//next即下一个要存放的位置
	head[n] = 1;//head[n]指向第n个物品第一个跳跃点的位置
	for (int i = n; i >= 1; i--)
	{
		int k = left;//k指向p[]中跳跃点，移动k来判断p[]与p[]+(w,v)中的受控点
		for (int j = left; j <= right; j++)
		{
			if (p[j][0] + w[i] > c)
				break;//剩余空间不能再装入i，退出for循环
			type y = p[j][0] + w[i], m = p[j][1] + v[i];//计算p[]+(w,v)
			//若p[k][0]较小则(p[k][0] p[k][1])一定不是受控点，将其作为p[i]的跳跃点存储
			while ((k <= right) && (p[k][0] < y))
			{
				p[next][0] = p[k][0];
				p[next++][1] = p[k++][1];
			}
			//如果p[k][0]==y而m<p[k][1],则(y m)为受控点不存
			if (k <= right&&p[k][0] == y)
			{
				if (m < p[k][1])
				{
					//对(p[k][0] p[k][1])进行判断
					m = p[k][1];
				}
				k++;
			}
			//若p[k][0]>=y且m>=p[k][1],判断是不是当前i的最后一个跳跃点的受控点
			//若不是则为i的跳跃点存储
			if (m>p[next - 1][1])
			{
				p[next][0] = y;
				p[next++][1] = m;
			}
			//若是，则对下一个元素进行判断
			while (k <= right&&p[k][1] <= p[next - 1][1])
			{
				k++;
			}
		}
		while (k <= right)
		{
			p[next][0] = p[k][0];
			p[next++][1] = p[k++][1];//将i+1剩下的跳跃点作为i的跳跃点存储
		}
		left = right + 1;
		right = next - 1;
		//第i-1个物品第一个跳跃点的位置head[0]指第0个物品第一个跳跃点的位置
		head[i - 1] = next;
	}
	Traceback(n, w, v, p, head, x);
	return p[next - 1][1];
}
//x[]数组存储对应物品0-1向量，0不装入，1表示装入背包
template<class type>void Traceback(int n, type w[], type v[], type**p, int *head, int x[])
{
	//初始化j，m为最后一个跳跃点对应的第0列以及第1列
	type j = p[head[0] - 1][0], m = p[head[0] - 1][1];
	for (int i = 1; i <= n; i++)
	{
		x[i] = 0;//初始化数组
		for (int k = head[i + 1]; k <= head[i] - 1; k++)
		{
			//判断物品i是否装入
			if ((p[k][0] + w[i] == j) && (p[k][1] + v[i] == m))
			{
				x[i] = 1;//物品i被装入，则x[i]置1
				j = p[k][0];//j和m值置为满足if条件的跳跃点对应的值
				m = p[k][1];
				break;//接着再判断下一个物品
			}
		}
	}
}