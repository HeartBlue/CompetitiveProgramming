/*
Learn to solve 2-sat. Output a solution of 2-sat
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
vector<int> v2[N];
int deg[N];
int arc[N];
int clr[N];
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
void solve(int n)
{
	memset(in, 0, sizeof(int)*n);
	memset(dfn, 0, sizeof(int)*n);
	top = cnt = scccnt = 0;
	for (int i = 0; i < n; i++)
	{
		if (!dfn[i])
			tarjan(i);
	}
	for (int i = 0; i < n; i += 2)
	{
		int x = belong[i], y = belong[i + 1];
		if (x == y)
		{
			puts("bad luck");
			return;
		}
		arc[x] = y;
		arc[y] = x;
	}
	memset(deg, 0, sizeof(int)*(scccnt + 1));
	memset(clr, 0, sizeof(int)*(scccnt + 1));
	for (int i = 1; i <= scccnt; i++) v2[i].clear();
	for (int i = 0; i < n; i++)
	{
		int x = belong[i];
		for (int j = 0; j < v[i].size(); j++)
		{
			int y = belong[v[i][j]];
			if (x == y) continue;
			v2[y].push_back(x);
			//cout << y << ' ' << x << endl;
			deg[x]++;
		}
	}
	queue<int> q;
	for (int i = 1; i <= scccnt; i++)
	{
		if (deg[i] == 0)
			q.push(i);
	}
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		if (clr[x] == 0)
		{
			clr[x] = 1;
			clr[arc[x]] = 2;
		}
		for (int i = 0; i < v2[x].size(); i++)
		{
			int y = v2[x][i];
			deg[y]--;
			if (deg[y] == 0) q.push(y);
		}
	}
	for (int i = 2; i < n; i += 2)
	{
		if (i != 2) putchar(' ');
		printf("%d", i / 2);
		if (clr[belong[i]] == clr[belong[0]]) putchar('w');
		else putchar('h');
	}
	puts("");
}
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF)
	{
		if (n == 0 && m == 0) break;
		for (int i = 0; i < n * 2; i++) v[i].clear();
		while (m--)
		{
			int x, y;
			char c1, c2;
			scanf("%d%c %d%c", &x, &c1, &y, &c2);
			x = x << 1 | (c1 == 'w');
			y = y << 1 | (c2 == 'w');
			v[x].push_back(y ^ 1);
			v[y].push_back(x ^ 1);
		}
		v[1].push_back(0);
		solve(2 * n);
	}
	return 0;
}