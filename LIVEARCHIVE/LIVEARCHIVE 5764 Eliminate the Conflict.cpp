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
const int N = 1e5;
vector<int> v[N];
int low[N], dfn[N];
int in[N], s[N], top;
int belong[N];
int cnt, scccnt;
void tarjan(int x)
{
	low[x] = dfn[x] = ++cnt;
	in[x] = 1;
	s[top++] = x;
	for (int i = 0; i < v[x].size(); i++)
	{
		int y = v[x][i];
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
			in[y] = 0;
			belong[y] = scccnt;
			if (x == y) break;
		}
	}
}
void init(int n)
{
	memset(in, 0, sizeof(int)*n);
	memset(dfn, 0, sizeof(int)*n);
	top = cnt = scccnt = 0;
	for (int i = 0; i < n; i++)
	{
		if (!dfn[i])
			tarjan(i);
	}
}
int a[N][2];
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int ncase;
	scanf("%d", &ncase);
	int ks = 1;
	while (ncase--)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++)
		{
			int o;
			scanf("%d", &o);
			a[i][1] = o % 3;
			a[i][0] = o - 1;
		}
		for (int i = 0; i < 2 * n; i++) v[i].clear();
		while (m--)
		{
			int x, y, o;
			scanf("%d%d%d", &x, &y, &o);
			for (int o1 = 0; o1 < 2; o1++)
			{
				for (int o2 = 0; o2 < 2; o2++)
				{
					if ((a[x][o1] == a[y][o2]) ^ o) continue;
					{
						int X = (x - 1) << 1 | o1;
						int Y = (y - 1) << 1 | o2;
						v[X].push_back(Y ^ 1);
						v[Y].push_back(X ^ 1);
					}
				}
			}
		}
		init(2 * n);
		int flag = 1;
		for (int i = 0; i < n * 2; i += 2)
		{
			if (belong[i] == belong[i ^ 1])
			{
				flag = 0;
				break;
			}
		}
		if (flag) printf("Case #%d: yes\n", ks++);
		else printf("Case #%d: no\n", ks++);
	}
	return 0;
}