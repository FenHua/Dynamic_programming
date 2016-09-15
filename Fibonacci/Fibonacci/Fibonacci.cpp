/*Fibonacci.cpp : �������̨Ӧ�ó������ڵ㡣
fib(5)�ļ����������:
fib(5)
fib(4) + fib(3)
(fib(3) + fib(2)) + (fib(2) + fib(1))
((fib(2) + fib(1)) + (fib(1) + fib(0))) + ((fib(1) + fib(0)) + fib(1))
(((fib(1) + fib(0)) + fib(1)) + (fib(1) + fib(0))) + ((fib(1) + fib(0)) + fib(1))
��������Կ����������㷨�������Ƶ�������������ظ��ļ��㣬��˲���һ�ָ�Ч���㷨��ʵ���ϣ����㷨������ʱ����ָ���������ġ�
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
	cout << "������n��" << endl;
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

//��ǰn���Ѿ������ǰn��������������map�У������ں���ļ����п���ֱ������ǰ��Ľ�����Ӷ��������ظ����㡣�㷨������ʱ���ΪO(n)��
#include<map>
//Map��c++��һ����׼���������ṩ�˺ܺ�һ��һ�Ĺ�ϵ
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
	cout << "������n��" << endl;
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
		//find()��������һ��������ָ���ֵΪkey��Ԫ�أ����û�ҵ��ͷ���ָ��mapβ���ĵ�������
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