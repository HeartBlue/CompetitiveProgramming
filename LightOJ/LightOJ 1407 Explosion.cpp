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
bool solve(int n)
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
			return false;
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
	printf("Possible ");
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
	puts(".");
	return true;
}
struct Node
{
	int a[3];
	int o;
	void init()
	{
		scanf("%d", &o);
		for (int i = 0; i < 3; i++)
		{
			scanf("%d", &a[i]);
			a[i]--;
		}
	}
	void refrain(int pos)
	{
		int x = a[pos] << 1;
		if (o == 1)
		{
			v[x ^ 1].push_back(x);
		}
		else
		{
			v[x].push_back(x ^ 1);
		}
	}
} node[10];
vector<pair<int, int> > vp;
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int ncase;
	scanf("%d", &ncase);
	int ks = 1;
	while (ncase--)
	{
		vp.clear();
		int n, m, k;
		scanf("%d%d%d", &n, &m, &k);
		while (m--)
		{
			int op, x, y;
			scanf("%d%d%d", &op, &x, &y);
			x = (x - 1) << 1;
			y = (y - 1) << 1;
			if (op == 1)
			{
				vp.push_back({ x ^ 1, y });
			}
			if (op == 2)
			{
				vp.push_back({ x ^ 1,y ^ 1 });
			}
			if (op == 3)
			{
				vp.push_back({ x,y ^ 1 });
			}
			if (op == 4)
			{
				vp.push_back({ x,y ^ 1 });
				vp.push_back({ x ^ 1,y });
			}
		}
		for (int i = 0; i < k; i++)
			node[i].init();
		int cnt[10];
		MEM(cnt, 0);
		int flag = 0;
		printf("Case %d: ", ks++);
		while (cnt[k] == 0)
		{
			for (int i = 0; i < 2 * n; i++) v[i].clear();
			for (int i = 0; i < vp.size(); i++)
			{
				int x = vp[i].first;
				int y = vp[i].second;
				v[x].push_back(y);
				v[y ^ 1].push_back(x ^ 1);
			}
			for (int i = 0; i < k; i++)
			{
				node[i].refrain(cnt[i]);
			}
			if (solve(2 * n))
			{
				flag = 1;
				break;
			}
			cnt[0]++;
			for (int i = 0; i < k; i++)
			{
				if (cnt[i] >= 3) cnt[i] = 0, cnt[i + 1]++;
			}
		}
		if (flag == 0) puts("Impossible.");
	}
	return 0;
}