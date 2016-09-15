/*Fibonacci.cpp : 定义控制台应用程序的入口点。
fib(5)的计算过程如下:
fib(5)
fib(4) + fib(3)
(fib(3) + fib(2)) + (fib(2) + fib(1))
((fib(2) + fib(1)) + (fib(1) + fib(0))) + ((fib(1) + fib(0)) + fib(1))
(((fib(1) + fib(0)) + fib(1)) + (fib(1) + fib(0))) + ((fib(1) + fib(0)) + fib(1))
由上面可以看出，这种算法对于相似的子问题进行了重复的计算，因此不是一种高效的算法。实际上，该算法的运算时间是指数级增长的。
*/

#include "stdafx.h"
#include"iostream"
using namespace std;
/*
void input(int &n);
int fib(int n);

int main()
{
	int n;
	input(n);
	cout << "fib(" << n << ")=" << fib(n) << endl;
	return 0;
}

void input(int &n)
{
	cout << "请输入n：" << endl;
	cin >> n;
}
int fib(int n)
{
	if (n == 0 || n == 1)
	{
		return 1;
	}
	else
	{
		return fib(n - 1) + fib(n - 2);
	}
}
*/

//将前n个已经算出的前n个数保存在数组map中，这样在后面的计算中可以直接易用前面的结果，从而避免了重复计算。算法的运算时间变为O(n)。
#include<map>
//Map是c++的一个标准容器，她提供了很好一对一的关系
void input(int&n);
int fib(int n, map<int, int>);

int main()
{
	map<int, int>my_Map;
	int n;
	input(n);
	cout << "fib(" << n << ")=" << fib(n, my_Map) << endl;
	return 0;
}
void input(int&n)
{
	cout << "请输入n：" << endl;
	cin >> n;
}
int fib(int n, map<int, int>my_Map)
{
	if (n == 0 || n == 1)
	{
		return 1;
	}
	else
	{
		map<int, int>::iterator iter = my_Map.find(n);
		//find()函数返回一个迭代器指向键值为key的元素，如果没找到就返回指向map尾部的迭代器。
		if (iter == my_Map.end())
		{
			int temp = fib(n - 1, my_Map) + fib(n - 2, my_Map);
			my_Map.insert(pair<int, int>(n, temp));
			return temp;
		}
		else
		{
			return iter->second;
		}
	}
}