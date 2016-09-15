// Dynamic_LCS.cpp : 定义控制台应用程序的入口点。
//最长公共字串的动态规划实现
//

#include "stdafx.h"
#include"iostream"
#include<string>
using namespace std;

string getLCSLength(string&s, string&t);


int main()
{
	string s, t;
	cout << "请输入字符串s：" << endl;
	cin >> s;
	cout << "请输入字符串t：" << endl;
	cin >> t;
	cout << "最长公共字串为：" << endl;
	cout << getLCSLength(s, t) << endl;
	return 0;
}

string getLCSLength(string&s, string&t)
{
	int p = s.length();
	int q = t.length();
	string **num = new string*[p];
	for (int i = 0; i < p; i++)
	{
		num[i] = new string[q];
	}
	char char1 = '\0';
	char char2 = '\0';
	int len = 0;
	string lcs = "";
	for (int i = 0; i < p; i++)
	{
		for (int j = 0; j <q; j++)
		{
			char1 = s.at(i);
			char2 = t.at(j);
			if (char1 != char2)
			{
				num[i][j] = "";
			}
			else
			{
				if ((i == 0) || (j == 0))
				{
					num[i][j] = char1;
				}
				else
				{
					num[i][j] = num[i-1][j-1] + char1;
				}
				if (num[i][j].length() > len)
				{
					len = num[i][j].length();
					lcs = num[i][j];
				}
				else if (num[i][j].length() == len)
				{
					lcs = lcs + "," + num[i][j];
				}
			}
		}
	}
	for (int i = 0; i < p; i++)
	{
		delete[]num[i];
	}
	delete[]num;
	return lcs;
}
