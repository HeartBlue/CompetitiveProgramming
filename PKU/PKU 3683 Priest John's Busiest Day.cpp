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
int l[N], r[N], d[N];
pair<int, int> check(int i, int o)
{
	if (o == 0) return make_pair(l[i], l[i] + d[i]);
	else return make_pair(r[i] - d[i], r[i]);
}
bool check(pair<int, int> p1, pair<int, int> p2)
{
	return max(p1.first, p2.first) < min(p1.second, p2.second);
}
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
			puts("NO");
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
		for (int j = 0; j < v[i].size(); j++)
		{
			int x = belong[i];
			int y = belong[v[i][j]];
			if (x == y) continue;
			deg[x]++;
			v2[y].push_back(x);
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
	puts("YES");
	for (int i = 0; i < n; i += 2)
	{
		pair<int, int> p = check(i / 2, clr[belong[i]] == 1 ? 0 : 1);
		printf("%02d:%02d %02d:%02d\n", p.first / 60, p.first % 60, p.second / 60, p.second % 60);
	}
}

int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n;
	while (scanf("%d", &n) != EOF)
	{
		for (int i = 0; i < n; i++)
		{
			int h1, m1, h2, m2;
			scanf("%d:%d %d:%d%d", &h1, &m1, &h2, &m2, &d[i]);
			l[i] = h1 * 60 + m1;
			r[i] = h2 * 60 + m2;
		}
		for (int i = 0; i < 2 * n; i++) v[i].clear();
		for (int i = 0; i < n; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				for (int o1 = 0; o1 < 2; o1++)
				{
					for (int o2 = 0; o2 < 2; o2++)
					{
						int x = i << 1 | o1;
						int y = j << 1 | o2;
						if (check(check(i, o1), check(j, o2)))
						{
							v[x].push_back(y ^ 1);
							v[y].push_back(x ^ 1);
						}
					}
				}
			}
		}
		solve(2 * n);
	}
	return 0;
}