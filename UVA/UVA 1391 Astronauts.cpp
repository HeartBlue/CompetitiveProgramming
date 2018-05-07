/*
learn to solve 2-sat. output a solution of 2-sat.
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
const int N = 2e5 + 10;
int low[N], dfn[N];
int in[N], s[N];
int belong[N];
int cnt, scccnt, top;
vector<int> v1[N], v2[N];
int arc[N];
int clr[N];
int deg[N];
int age[N];
void tarjan(int x)
{
	dfn[x] = low[x] = ++cnt;
	in[x] = 1;
	s[top++] = x;
	for (auto &y : v1[x])
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
			in[y] = 0;
			belong[y] = scccnt;
			if (y == x) break;
		}
	}
}
void solve(int n, string &str)
{
	memset(dfn, 0, sizeof(int)*n);
	memset(in, 0, sizeof(int)*n);
	top = scccnt = cnt = 0;
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
			puts("No solution.");
			return;
		}
		arc[x] = y;
		arc[y] = x;
	}
	for (int i = 1; i <= scccnt; i++) v2[i].clear();
	memset(deg, 0, sizeof(int)*(scccnt + 1));
	memset(clr, 0, sizeof(int)*(scccnt + 1));
	for (int i = 0; i < n; i++)
	{
		for (auto &j : v1[i])
		{
			int x = belong[i];
			int y = belong[j];
			if (x == y) continue;
			v2[y].push_back(x);
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
		if (!clr[x])
		{
			clr[x] = 1;
			clr[arc[x]] = 2;
		}
		for (auto &y : v2[x])
		{
			deg[y]--;
			if (deg[y] == 0) q.push(y);
		}
	}
	for (int i = 0; i < n; i += 2)
	{
		//cout << i / 2 + 1 << ' ';
		if (clr[belong[i]] == 1) printf("C\n");
		else printf("%c\n", str[i >> 1]);
	}
}
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF)
	{
		if (n == 0 && m == 0) break;
		for (int i = 0; i < 2 * n; i++) v1[i].clear();
		int tot = 0;
		for (int i = 0; i < n; i++)
		{
			scanf("%d", &age[i]);
			tot += age[i];
		}
		string str(n, 'A');
		for (int i = 0; i < n; i++)
		{
			if (age[i] * n < tot) str[i] = 'B';
		}
		while (m--)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			x--, y--;
			if (str[x] == str[y])
			{
				x <<= 1, y <<= 1;
				v1[x].push_back(y ^ 1);
				v1[x ^ 1].push_back(y);
				v1[y].push_back(x ^ 1);
				v1[y ^ 1].push_back(x);
			}
			else
			{
				x <<= 1, y <<= 1;
				v1[x].push_back(y ^ 1);
				v1[y].push_back(x ^ 1);
			}
		}
		solve(2 * n, str);
	}
	return 0;
}