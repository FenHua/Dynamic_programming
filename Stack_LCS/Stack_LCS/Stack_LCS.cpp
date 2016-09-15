/*Stack_LCS.cpp : �������̨Ӧ�ó������ڵ㡣
�㷨��Ҫ����������ջstore,print��һ����������ڵ㣬һ��������ӡ�ڵ㡣
*/
//������ִ�LSC��������
#include "stdafx.h"
#include"Stack.h"
#include"iostream"
using namespace std;

typedef int **Matrix;
const int M = 7;
const int N = 6;

typedef struct _Element
{
	int lcslen;//��ǰ�ڵ��LCS����
	int row;//��ǰ�ڵ��������
	int col;//��ǰ�ڵ��������
}Element;
void output(char*s, int n);
Element CreateElement(int nlen, int row, int col);
Matrix GreateMatrix(int row, int col);
void Deletematrix(Matrix p, int row);
void printStack(Stack<Element>*ps, char *str, int len);
void SearchE(Matrix pb, int curposx, int curposy, int &eposx, int&eposy, int ntype);
void LCSLength(int m, int n, char*x, char*y, Matrix pc, Matrix pb);
void LCS(char *x, Matrix pc, Matrix pb, int row, int col);//�����������


int main()
{
	char x[] = { ' ', 'A', 'B', 'C', 'B', 'D', 'A', 'B' };
	char y[] = { ' ', 'B', 'D', 'C', 'A', 'B', 'A' };
	Matrix b = GreateMatrix(M, N);
	Matrix c = GreateMatrix(M, N);
	LCSLength(M, N, x, y, c, b);
	cout << "����X��" << endl;
	output(x, M);
	cout << "����Y��" << endl;
	output(y, N);
	cout << "����X,Y����������г���Ϊ��" << c[M][N] << endl;
	cout << "����X,Y�����������Ϊ��" << endl;
	LCS(x, c, b, M, N);
	Deletematrix(b, M);
	Deletematrix(c, M);
	return 0;
}

void output(char*s, int n)
{
	for (int i = 1; i <= n; i++)
	{
		cout << s[i] << " ";
	}
	cout << endl;
}
Element CreateElement(int nlen, int row, int col)
{
	Element ele;
	ele.lcslen = nlen;
	ele.col = col;
	ele.row = row;
	return ele;
}
Matrix GreateMatrix(int row, int col)
{
	Matrix p = new int *[row + 1];
	for (int i = 0; i <= row; i++)
	{
		p[i] = new int[col + 1];
	}
	return p;
}
void Deletematrix(Matrix p, int row)
{
	for (int i = 0; i <= row; i++)
	{
		delete []p[i];
	}
	delete[]p;
}
void PrintStack(Stack<Element>*s, char*str, int len)
{
	if (s == NULL || str == NULL)
	{
		return;
	}
	StackNode<Element>*sn = s->GetStackNode();
	while ((sn != NULL) && (sn->data.row <= len))
	{
		cout << str[sn->data.row] <<" ";
		sn = sn->next;
	}
	cout << endl;
}
void SearchE(Matrix pb, int curposx, int curposy, int &eposx, int &eposy, int ntype)
{
	switch (pb[curposx][curposy])
	{
	case 1:
		eposx = curposx;
		eposy = curposy;
		return;
	case 2:
		SearchE(pb, curposx - 1, curposy, eposx, eposy, ntype);
		break;
	case 3:
		SearchE(pb, curposx, curposy - 1, eposx, eposy, ntype);
		break;
	case 4:
		if (ntype == 0)
			//����e1�㣬�������ֲ�㣬���ϼ�������
			SearchE(pb, curposx - 1, curposy, eposx, eposy, ntype);
		else
			//����e2�㣬�������ֲ�㣬�����������
			SearchE(pb, curposx, curposy - 1,eposx, eposy, ntype);
		break;
	}
}
void LCSLength(int m, int n, char*x, char*y, Matrix pc, Matrix pb)
{
	int i, j;
	for (i = 1; i <= m; i++)
		pc[i][0] = 0;
	for (i = 1; i <= n; i++)
		pc[0][i] = 0;
	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (x[i] == y[j])
			{
				pc[i][j] = pc[i - 1][j - 1] + 1;
				pb[i][j] = 1;
			}
			else if (pc[i - 1][j] > pc[i][j - 1])
			{
				pc[i][j] = pc[i - 1][j];
				pb[i][j] = 2;
			}
			else if (pc[i - 1][j] < pc[i][j - 1])
			{
				pc[i][j] = pc[i][j - 1];
				pb[i][j] = 3;
			}
			else
			{
				pc[i][j] = pc[i][j - 1];//����ڵ���Ͻڵ�ת�ƶ���
				pb[i][j] = 4;//���Ϊ4
			}
		}
	}
}
void LCS(char*x, Matrix pc, Matrix pb, int row, int col)
{
	if (x == NULL || pc == NULL || pb == NULL)
		return;
	Stack<Element>store, print;//��������ջstore,print
	Element storetop;//storeջ���ڵ�
	Element element;//��ʱ����
	Element virtualnode;//����ڵ�
	int ntoplen;//����storeջ���ڵ��LCS����
	int ex1, ey1, ex2, ey2;//���������������ڵ������
	int i, j;
	virtualnode=CreateElement(pc[row][col] + 1, row + 1, col + 1);
	store.Push(virtualnode);//ѹ������ڵ㵽store
	while (!store.IsEmpty())
	{
		store.Pop(&storetop);
		if ((storetop.row == 1) || (storetop.col == 1))
		{
			//����Ǳ߽��
			print.Push(storetop);
			PrintStack(&print, x, row);//��ӡprintջ�����������ڵ�֮������еĽڵ�
			store.Peek(&element);
			ntoplen = element.lcslen;//��ǰstore��ջ���ڵ��LSC����
			while (print.Peek(&element) && element.lcslen <= ntoplen)
			{
				//����printջ������LSC����С�ڵ���ntoplen�Ľڵ�
				print.Pop(&element);
			}
		}
		else
		{
			print.Push(storetop);
			SearchE(pb, storetop.row - 1, storetop.col - 1, ex1, ey1, 0);
			SearchE(pb, storetop.row - 1, storetop.col - 1, ex2, ey2, 1);//����ֵҲ����
			if ((ex1 == ex2)&&(ey1 == ey2))
			{
				element = CreateElement(pc[ex1][ey1], ex1, ey1);
				store.Push(element);//ѹ��ջ���ص�����2
			}
			else
			{
				for (i = ex1; i <= ex2; i++)
				{
					for (j = ey2; j <= ey1; j++)
					{
						if (pb[i][j] == 1)
						{
							element = CreateElement(pc[i][j], i, j);
							store.Push(element);
						}
					}
				}
			}
		}
	}
}