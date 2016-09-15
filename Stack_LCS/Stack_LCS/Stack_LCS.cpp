/*Stack_LCS.cpp : 定义控制台应用程序的入口点。
算法主要是利用两个栈store,print，一个用来储存节点，一个用来打印节点。
*/
//最长公共字串LSC矩阵搜索
#include "stdafx.h"
#include"Stack.h"
#include"iostream"
using namespace std;

typedef int **Matrix;
const int M = 7;
const int N = 6;

typedef struct _Element
{
	int lcslen;//当前节点的LCS长度
	int row;//当前节点的行坐标
	int col;//当前节点的列坐标
}Element;
void output(char*s, int n);
Element CreateElement(int nlen, int row, int col);
Matrix GreateMatrix(int row, int col);
void Deletematrix(Matrix p, int row);
void printStack(Stack<Element>*ps, char *str, int len);
void SearchE(Matrix pb, int curposx, int curposy, int &eposx, int&eposy, int ntype);
void LCSLength(int m, int n, char*x, char*y, Matrix pc, Matrix pb);
void LCS(char *x, Matrix pc, Matrix pb, int row, int col);//矩阵回溯搜索


int main()
{
	char x[] = { ' ', 'A', 'B', 'C', 'B', 'D', 'A', 'B' };
	char y[] = { ' ', 'B', 'D', 'C', 'A', 'B', 'A' };
	Matrix b = GreateMatrix(M, N);
	Matrix c = GreateMatrix(M, N);
	LCSLength(M, N, x, y, c, b);
	cout << "序列X：" << endl;
	output(x, M);
	cout << "序列Y：" << endl;
	output(y, N);
	cout << "序列X,Y最长公共子序列长度为：" << c[M][N] << endl;
	cout << "序列X,Y最长公共子序列为：" << endl;
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
			//搜索e1点，如碰到分叉点，向上继续搜索
			SearchE(pb, curposx - 1, curposy, eposx, eposy, ntype);
		else
			//搜索e2点，如碰到分叉点，向左继续搜索
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
				pc[i][j] = pc[i][j - 1];//由左节点或上节点转移而来
				pb[i][j] = 4;//标记为4
			}
		}
	}
}
void LCS(char*x, Matrix pc, Matrix pb, int row, int col)
{
	if (x == NULL || pc == NULL || pb == NULL)
		return;
	Stack<Element>store, print;//构造两个栈store,print
	Element storetop;//store栈顶节点
	Element element;//临时变量
	Element virtualnode;//虚拟节点
	int ntoplen;//保存store栈顶节点的LCS长度
	int ex1, ey1, ex2, ey2;//矩形搜索的两个节点的坐标
	int i, j;
	virtualnode=CreateElement(pc[row][col] + 1, row + 1, col + 1);
	store.Push(virtualnode);//压入虚拟节点到store
	while (!store.IsEmpty())
	{
		store.Pop(&storetop);
		if ((storetop.row == 1) || (storetop.col == 1))
		{
			//如果是边界点
			print.Push(storetop);
			PrintStack(&print, x, row);//打印print栈里面除了虚拟节点之外的所有的节点
			store.Peek(&element);
			ntoplen = element.lcslen;//当前store的栈顶节点的LSC长度
			while (print.Peek(&element) && element.lcslen <= ntoplen)
			{
				//弹出print栈中所有LSC长度小于等于ntoplen的节点
				print.Pop(&element);
			}
		}
		else
		{
			print.Push(storetop);
			SearchE(pb, storetop.row - 1, storetop.col - 1, ex1, ey1, 0);
			SearchE(pb, storetop.row - 1, storetop.col - 1, ex2, ey2, 1);//其它值也可以
			if ((ex1 == ex2)&&(ey1 == ey2))
			{
				element = CreateElement(pc[ex1][ey1], ex1, ey1);
				store.Push(element);//压入栈，回到步骤2
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