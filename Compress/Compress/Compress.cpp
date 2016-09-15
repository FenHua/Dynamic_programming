/*Compress.cpp : �������̨Ӧ�ó������ڵ㡣
�����������ڼ�����У��������ص�ĻҶ�ֵ����{p1,p1,����pn}��ʾͼ����������pi,1<=i<=n����ʾ���ص�i�ĻҶ�ֵ��
ͨ���Ҷ�ֵ�ķ�Χ��0~255����������Ҫ8λ��ʾһ�����ء�ѹ����ԭ����ǰ�����{p1,p1,����pn}������ϵ㣬����ָ�
��һ��һ�εġ��ֶεĹ��̾���Ҫ�ҳ��ϵ㣬��һ����������ص����Ҷ�ֵ�Ƚ�С����ô��һ������(������Ҫ8λ)�Ϳ���
�ý��ٵ�λ(����7λ)����ʾ���Ӷ����ٴ洢�ռ䡣b����bits,l����length,�ֶ��ǣ�b[i]��ʾÿ��һ�����ص���Ҫ�����ٴ洢
�ռ�(����8λ��������)��l[i]��ʾÿ�������ж��ٸ����ص㣬s[i]��ʾ��0��iѹ��Ϊһ��ռ���ٴ洢�ռ䡣�������l[i]<=255,����Ҫ8λ����ʾl[i]��
��b[i]<=8����Ҫ3λ��ʾb[i]������ÿ������Ĵ洢�ռ�Ϊl[i]*b[i]+11λ�����轫ԭͼ��ֳ�m�Σ���ô��Ҫλ�Ĵ洢�ռ䡣ͼ��ѹ������
����Ҫȷ����������{p1,p1,����pn}�����ŷֶΣ�ʹ�����˷ֶ�����Ĵ洢�ռ���С��
*/

#include "stdafx.h"
#include"iostream"
using namespace std;

const int N = 7;
int length(int i);
void Compress(int n, int p[], int s[], int l[], int b[]);
void Traceback(int n, int&i, int s[], int l[]);
void Output(int s[],int l[],int b[],int n);

int main()
{
	int p[] = { 0, 10, 12, 15, 255, 1, 2 };//ͼ��Ҷ����� �±��1��ʼ����  
	int s[N], l[N], b[N];
	cout << "ͼ��ĻҶ�����Ϊ��" << endl;
	for (int i = 1; i<N; i++)
	{
		cout << p[i] << " ";
	}
	cout << endl;
	Compress(N - 1, p, s, l, b);
	Output(s, l, b, N - 1);
	return 0;
}

void Compress(int n, int p[], int s[], int l[], int b[])
{
	int Lmax = 256, header = 11;
	s[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		b[i] = length(p[i]);//�������ص�p��Ҫ�Ĵ洢λ��
		int bmax = b[i];
		s[i] = s[i - 1] + bmax;//������ռ�Ŀռ��С
		l[i] = 1;
		for (int j = 2; (j <= i&&j <= Lmax); j++)
		{
			if (bmax < b[i - j + 1])
			{
				bmax = b[i - j + 1];
			}
			if (s[i]>s[i - j] + j*bmax)
			{
				s[i] = s[i - j] + j*bmax;
				l[i] = j;
			}
		}
		s[i] += header;
	}
}
int length(int i)
{
	int k = 1;
	i = i / 2;
	while (i > 0)
	{
		k++;
		i = i / 2;
	}
	return k;
}
void Traceback(int n, int&i, int s[], int l[])
{
	if (n == 0)
		return;
	Traceback(n - l[n],i,s,l);
	s[i++] = n - l[n];//����Ϊ����s��ֵ�������洢�ֶ�λ��
}
void Output(int s[], int l[], int b[], int n)
{
	//�����s[n]�洢λ����s[]���������¸�ֵ�������洢�ֶε�λ��
	cout << "ͼ��ѹ�������С�ռ�Ϊ��" << s[n] << endl;
	int m = 0;
	Traceback(n, m, s, l);
	s[m] = n;
	cout << "��ԭ�Ҷ����зֳ�" << m << "������" << endl;
	for (int j = 1; j <= m; j++)
	{
		l[j] = l[s[j]];
		b[j] = b[s[j]];
	}
	for (int j = 1; j <= m; j++)
	{
		cout << "�γ��ȣ�" << l[j] << ",����Ҫ�洢λ����" << b[j] << endl;
	}
}