/*
given a graph with n nodes and m undirected weighted edges.
For each graph, there are q queries.
for each query, you need to find a path from S to T, in the path the maximum edge is minimum, output the value.

Just construct the MST, and find the maximun edge in the path from S to T.
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
const int N = 1e5 + 10;
int fa[N][20];
int maxv[N][20];
int depth[N];
vector<pair<int, int>> v[N];
class UnionFind
{
public:
	int a[N];
	void init(int n = N)
	{
		memset(a, -1, sizeof(int)*n);
	}
	int Find(int x)
	{
		int s = x;
		while (a[s] >= 0) s = a[s];
		while (x != s)
		{
			int t = a[x];
			a[x] = s;
			x = t;
		}
		return s;
	}
	void Union(int x, int y)
	{
		int px = Find(x);
		int py = Find(y);
		if (a[px] > a[py]) swap(px, py);
		a[px] += a[py];
		a[py] = px;
	}
} uf;
void dfs(int x, int p = 0)
{
	fa[x][0] = p;
	depth[x] = depth[p] + 1;
	for (auto &pp : v[x])
	{
		int y, w;
		tie(y, w) = pp;
		if (y == p) continue;
		maxv[y][0] = w;
		dfs(y, x);
	}
}
void init(int n)
{
	dfs(1);
	for (int o = 1; o < 20; o++)
	{
		for (int i = 1; i <= n; i++)
		{
			int p = fa[i][o - 1];
			fa[i][o] = fa[p][o - 1];
			maxv[i][o] = max(maxv[i][o - 1], maxv[p][o - 1]);
		}
	}
}
int moveup(int x, int d)
{
	for (int i = 0; (1 << i) <= d; i++)
	{
		if (d >> i & 1)
			x = fa[x][i];
	}
	return x;
}
int getlca(int x, int y)
{
	if (depth[x] < depth[y]) swap(x, y);
	x = moveup(x, depth[x] - depth[y]);
	if (x == y) return x;
	for (int i = 19; i >= 0; i--)
	{
		if (fa[x][i] != fa[y][i])
			x = fa[x][i], y = fa[y][i];
	}
	return fa[x][0];
}
int getmax(int x, int d)
{
	int ret = 0;
	for (int i = 0; (1 << i) <= d; i++)
	{
		if (d >> i & 1)
		{
			ret = max(ret, maxv[x][i]);
			x = fa[x][i];
		}
	}
	return ret;
}
int solve(int x, int y)
{
	int lca = getlca(x, y);
	return max(getmax(x, depth[x] - depth[lca]), getmax(y, depth[y] - depth[lca]));
}
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n, m;
	int flag = 0;
	while (scanf("%d%d", &n, &m) != EOF)
	{
		if (flag) puts("");
		flag = 1;
		for (int i = 1; i <= n; i++) v[i].clear();
		uf.init();
		vector<tuple<int, int, int>> vp;
		for (int i = 0; i < m; i++)
		{
			int x, y, w;
			scanf("%d%d%d", &x, &y, &w);
			vp.push_back({ w,x,y });
		}
		sort(vp.begin(), vp.end());
		for (auto &p : vp)
		{
			int w, x, y;
			tie(w, x, y) = p;
			if (uf.Find(x) == uf.Find(y)) continue;
			uf.Union(x, y);
			v[x].push_back({ y,w });
			v[y].push_back({ x,w });
		}
		init(n);
		int q;
		scanf("%d", &q);
		while (q--)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			printf("%d\n", solve(x, y));
		}

	}
	return 0;
}