/*
Learn to solve 2-sat
*/
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
#define MEM(a,b) memset((a),(b),sizeof(a))
const LL INF = 1e9 + 7;
const int N = 1e4 + 10;
vector<int> v[N];
int low[N], dfn[N];
int in[N], top, s[N];
int belong[N];
int cnt;
int scccnt;
void tarjan(int x)
{
	dfn[x] = low[x] = ++cnt;
	in[x] = 1;
	s[top++] = x;
	for (auto &y : v[x])
	{
		if (dfn[y])
		{
			if (in[y]) low[x] = min(low[x], dfn[y]);
		}
		else
		{
			tarjan(y);
			low[x] = min(low[x], low[y]);
		}
	}
	if (low[x] == dfn[x])
	{
		scccnt++;
		while (1)
		{
			int y = s[--top];
			belong[y] = scccnt;
			in[y] = 0;
			if (y == x) break;
		}
	}
}
void init(int n)
{
	memset(dfn, 0, sizeof(int)*n);
	memset(in, 0, sizeof(int)*n);
	cnt = scccnt = 0;
	top = 0;
	for (int i = 0; i < n; i++)
	{
		if (!dfn[i])
			tarjan(i);
	}
}
int b[510][510];
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n;
	while (scanf("%d", &n) != EOF)
	{
		int flag = 1;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				scanf("%d", &b[i][j]);
			}
			if (b[i][i] != 0) flag = 0;
		}
		while (flag)
		{
			for (int i = 0; i < 2 * n; i++) v[i].clear();
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (i == j) continue;
					int x = i << 1;
					int y = j << 1;
					if (i % 2 == 1 && j % 2 == 1)
					{
						if (b[i][j] & 1)
						{
							v[x ^ 1].push_back(y);
							v[y ^ 1].push_back(x);
						}
						else
						{
							v[x].push_back(x ^ 1);
							v[y].push_back(y ^ 1);
						}
						continue;
					}
					if (i % 2 == 0 && j % 2 == 0)
					{
						if (b[i][j] & 1)
						{
							v[x ^ 1].push_back(x);
							v[y ^ 1].push_back(y);
						}
						else
						{
							v[x].push_back(y ^ 1);
							v[y].push_back(x ^ 1);
						}
						continue;
					}
					if (b[i][j] & 1)
					{
						v[x].push_back(y ^ 1);
						v[y].push_back(x ^ 1);
						v[y ^ 1].push_back(x);
						v[x ^ 1].push_back(y);
					}
					else
					{
						v[x].push_back(y);
						v[y].push_back(x);
						v[x ^ 1].push_back(y ^ 1);
						v[y ^ 1].push_back(x ^ 1);
					}
				}
			}
			init(2 * n);
			for (int i = 0; i < 2 * n; i += 2)
			{
				if (belong[i] == belong[i ^ 1])
				{
					flag = 0;
					break;
				}
			}
			LL sum = 0;
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					b[i][j] >>= 1;
					sum += b[i][j];
				}
			}
			if (sum == 0) break;
		}
		if (flag) puts("YES");
		else puts("NO");
	}
	return 0;
}