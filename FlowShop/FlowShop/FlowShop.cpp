/*FlowShop.cpp : �������̨Ӧ�ó������ڵ㡣
����������n����ҵ{1��2������n}Ҫ����2̨����M1��M2��ɵ���ˮ������ɼӹ���ÿ����
ҵ�ӹ���˳��������M1�ϼӹ���Ȼ����M2�ϼӹ���M1��M2�ӹ���ҵi�����ʱ��ֱ�Ϊai
��bi����ˮ��ҵ��������Ҫ��ȷ����n����ҵ�����żӹ�˳��ʹ�ôӵ�һ����ҵ�ڻ���M1�Ͽ�
ʼ�ӹ��������һ����ҵ�ڻ���M2�ϼӹ���������ʱ�����١�
��ˮ��ҵ��������Johnson�㷨
������ķ�����֪����ˮ��ҵ��������һ����������Johnson��������ŵ��ȣ���������������㷨ȷ����
��ˮ��ҵ���������Johnson�㷨��
(1)��N1={i|ai<bi},N2={i|ai>=bi};
(2)��N1����ҵ��ai�ķǼ������򣻽�N2����ҵ��bi�ķ���������
(3)N1����ҵ��N2����ҵ��������Johnson��������ŵ��ȡ�
�����ҵi��j����min{bi,aj} ��min{bj,ai},�����ҵi��j����Johnson����ʽ��
�����ҵi��j ������Johnson����ʽ���򽻻���ҵi��j����Johnson����ʽ��
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
void BubbleSort(Jobtype *d, int n);//ð������

int main()
{
	int a[] = { 2, 4, 3, 6, 1 };
	int b[] = { 5, 2, 3, 1, 7 };
	int c[N];
	int minTime = FlowShop(N, a, b, c);
	cout << "��ҵ�ڻ���1������ʱ��Ϊ��" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	cout << "��ҵ�ڻ���2�ϵ�����ʱ��Ϊ��" << endl;
	for (int i = 0; i < N; i++)
	{
		cout << b[i] << " ";
	}
	cout << endl;
	cout << "�����ҵ�����ʱ��Ϊ��" << minTime << endl;
	cout << "��Ŵ�0��ʼ����ҵ���ȵ�˳��Ϊ��" << endl;
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
		d[i].key = a[i]>b[i] ? b[i] : a[i];//��johnson����ֱ�ȡ��Ӧ��b[i]����a[i]��ֵ��Ϊ�ؼ���
		d[i].job = a[i] <= b[i];//��������a[i]<b[i]�ķ��뵽N1�Ӽ����Ϊtrue
		d[i].index = i;
	}
	BubbleSort(d, n);//������d���ؼ��������������
	int j = 0, k = n - 1;
	for (int i = 0; i < n; i++)
	{
		if (d[i].job)
		{
			c[j++] = d[i].index;//���Ź��������d��ȡ������ҵ�������N1�Ĵ�ǰ�����
		}
		else
		{
			c[k--] = d[i].index;//����N2�ĴӺ�����룬�Ӷ�ʵ��N1�ķǼ�����N2�ķ���������
		}
	}
	j = a[c[0]];
	k = j + b[c[0]];
	for (int i = 1; i < n; i++)
	{
		j += a[c[i]];//M1��ִ��c[i]��ҵ��ͬʱ��M2��ִ��c[i-1]����ҵ�����ִ��ʱ��ȡ����M1��M2˭��ִ����
		k = j < k ? k + b[c[i]] : j + b[c[i]];//�������żӹ�ʱ��
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