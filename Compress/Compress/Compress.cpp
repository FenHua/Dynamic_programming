/*Compress.cpp : 定义控制台应用程序的入口点。
问题描述：在计算机中，常用像素点的灰度值序列{p1,p1,……pn}表示图像。其中整数pi,1<=i<=n，表示像素点i的灰度值。
通常灰度值的范围是0~255。因此最多需要8位表示一个像素。压缩的原理就是把序列{p1,p1,……pn}进行设断点，将其分割
成一段一段的。分段的过程就是要找出断点，让一段里面的像素的最大灰度值比较小，那么这一段像素(本来需要8位)就可以
用较少的位(比如7位)来表示，从而减少存储空间。b代表bits,l代表length,分段是，b[i]表示每段一个像素点需要的最少存储
空间(少于8位才有意义)，l[i]表示每段里面有多少个像素点，s[i]表示从0到i压缩为一共占多少存储空间。如果限制l[i]<=255,则需要8位来表示l[i]。
而b[i]<=8，需要3位表示b[i]。所以每段所需的存储空间为l[i]*b[i]+11位。假设将原图像分成m段，那么需要位的存储空间。图像压缩问题
就是要确定像素序列{p1,p1,……pn}的最优分段，使得依此分段所需的存储空间最小。
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
	int p[] = { 0, 10, 12, 15, 255, 1, 2 };//图像灰度数组 下标从1开始计数  
	int s[N], l[N], b[N];
	cout << "图像的灰度序列为：" << endl;
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
		b[i] = length(p[i]);//计算像素点p需要的存储位数
		int bmax = b[i];
		s[i] = s[i - 1] + bmax;//像素所占的空间大小
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
	s[i++] = n - l[n];//重新为数组s赋值，用来存储分段位置
}
void Output(int s[], int l[], int b[], int n)
{
	//在输出s[n]存储位数后，s[]数组则被重新赋值，用来存储分段的位置
	cout << "图像压缩后的最小空间为：" << s[n] << endl;
	int m = 0;
	Traceback(n, m, s, l);
	s[m] = n;
	cout << "将原灰度序列分成" << m << "段序列" << endl;
	for (int j = 1; j <= m; j++)
	{
		l[j] = l[s[j]];
		b[j] = b[s[j]];
	}
	for (int j = 1; j <= m; j++)
	{
		cout << "段长度：" << l[j] << ",所需要存储位数：" << b[j] << endl;
	}
}