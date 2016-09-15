/*FlowShop.cpp : 定义控制台应用程序的入口点。
问题描述：n个作业{1，2，…，n}要在由2台机器M1和M2组成的流水线上完成加工。每个作
业加工的顺序都是先在M1上加工，然后在M2上加工。M1和M2加工作业i所需的时间分别为ai
和bi。流水作业调度问题要求确定这n个作业的最优加工顺序，使得从第一个作业在机器M1上开
始加工，到最后一个作业在机器M2上加工完成所需的时间最少。
流水作业调度问题Johnson算法
从上面的分析可知，流水作业调度问题一定存在满足Johnson法则的最优调度，且容易由下面的算法确定：
流水作业调度问题的Johnson算法：
(1)令N1={i|ai<bi},N2={i|ai>=bi};
(2)将N1中作业按ai的非减序排序；将N2中作业按bi的非增序排序；
(3)N1中作业接N2中作业构成满足Johnson法则的最优调度。
如果作业i和j满足min{bi,aj} ≥min{bj,ai},则称作业i和j满足Johnson不等式。
如果作业i和j 不满足Johnson不等式，则交换作业i和j满足Johnson不等式。
*/

#include "stdafx.h"
#include"iostream"
using namespace std;

const int N = 5;
class Jobtype
{
public:
	int key, index;
	bool job;
	int operator<=(Jobtype a)const
	{
		return (key <= a.key);
	}
};
int FlowShop(int n, int a[], int b[], int c[]);
void BubbleSort(Jobtype *d, int n);//冒泡排序

int main()
{
	int a[] = { 2, 4, 3, 6, 1 };
	int b[] = { 5, 2, 3, 1, 7 };
	int c[N];
	int minTime = FlowShop(N, a, b, c);
	cout << "作业在机器1上运行时间为：" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	cout << "作业在机器2上的运行时间为：" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << b[i] << " ";
	}
	cout << endl;
	cout << "完成作业的最短时间为：" << minTime << endl;
	cout << "编号从0开始，作业调度的顺序为：" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << c[i] << " ";
	}
	cout << endl;
	return 0;
}

int FlowShop(int n, int a[], int b[], int c[])
{
	Jobtype *d = new Jobtype[n];
	for (int i = 0; i < n; i++)
	{
		d[i].key = a[i]>b[i] ? b[i] : a[i];//按johnson法则分别取对应的b[i]或者a[i]的值作为关键字
		d[i].job = a[i] <= b[i];//符合条件a[i]<b[i]的放入到N1子集标记为true
		d[i].index = i;
	}
	BubbleSort(d, n);//对数组d按关键字升序进行排序
	int j = 0, k = n - 1;
	for (int i = 0; i < n; i++)
	{
		if (d[i].job)
		{
			c[j++] = d[i].index;//将排过序的数组d，取其中作业序号属于N1的从前面进入
		}
		else
		{
			c[k--] = d[i].index;//属于N2的从后面进入，从而实现N1的非减排序，N2的非增序排序
		}
	}
	j = a[c[0]];
	k = j + b[c[0]];
	for (int i = 1; i < n; i++)
	{
		j += a[c[i]];//M1在执行c[i]作业的同时，M2在执行c[i-1]号作业，最短执行时间取决于M1与M2谁后执行完
		k = j < k ? k + b[c[i]] : j + b[c[i]];//计算最优加工时间
	}
	delete d;
	return k;
}
void BubbleSort(Jobtype*d, int n)
{
	Jobtype temp;
	for (int i =0; i <n; i++)
	{
		for (int j = i + 1; j <n; j++)
		{
			if (d[j] <=d[i])
			{
				temp = d[i];
				d[i] = d[j];
				d[j] = temp;
			}
		}
	}
}