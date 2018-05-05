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
		int x = belong[i];
		int y = belong[i + 1];
		if (x == y)
		{
			puts("No");
			return;
		}
		arc[x] = y;
		arc[y] = x;
	}
	memset(clr, 0, sizeof(int)*(scccnt + 1));
	memset(deg, 0, sizeof(int)*(scccnt + 1));
	for (int i = 1; i <= scccnt; i++) v2[i].clear();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < v[i].size(); j++)
		{
			int x = belong[i];
			int y = belong[v[i][j]];
			if (x == y) continue;
			v2[y].push_back(x);
			deg[x]++;
		}
	}
	queue<int> q;
	for (int i = 1; i <= scccnt; i++)
	{
		if (deg[i] == 0) q.push(i);
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
	puts("Yes");
	vector<int> ans;
	for (int i = 0; i < n; i += 2)
	{
		if (clr[belong[i]] == 1)
			ans.push_back(i / 2 + 1);
	}
	printf("%d", ans.size());
	for (int i = 0; i < ans.size(); i++)
	{
		printf(" %d", ans[i]);
	}
	puts("");
}

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
		for (int i = 0; i < 2 * m; i++) v[i].clear();
		while (n--)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			if (x > 0) x = (x - 1) << 1;
			else x = (abs(x) - 1) << 1 | 1;
			if (y > 0) y = (y - 1) << 1;
			else y = (abs(y) - 1) << 1 | 1;
			v[x ^ 1].push_back(y);
			v[y ^ 1].push_back(x);
		}
		printf("Case %d: ", ks++);
		solve(2 * m);
	}
	return 0;
}