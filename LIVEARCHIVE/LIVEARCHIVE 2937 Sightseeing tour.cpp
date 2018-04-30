/*

Learn to solve Eulerian circuit with some edges are undirected and others are directed

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
const int M = 1e5 + 10;
struct Node
{
	int x, y, r, pre;
};
class Graph
{
public:
	int top[N];
	Node e[M];
	int k;
	void init(int sz = N)
	{
		memset(top, -1, sizeof(int)*sz);
		k = 0;
	}
	void addEdge(int x, int y, int w, int w2 = 0)
	{
		e[k] = Node{ x,y,w,top[x] };
		top[x] = k++;
		e[k] = Node({ y,x,w2,top[y] });
		top[y] = k++;
	}
	Node& operator [](int i)
	{
		return e[i];
	}
} g;
int layer[N];
int s, t;
int current[N];
bool bfs(int sz = N)
{
	memset(layer, -1, sizeof(int)*sz);
	layer[s] = 1;
	queue<int> q;
	q.push(s);
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		for (int i = g.top[x]; ~i; i = g[i].pre)
		{
			int y = g[i].y;
			int r = g[i].r;
			if (r > 0 && layer[y] == -1)
			{
				layer[y] = layer[x] + 1;
				q.push(y);
				if (y == t) return true;
			}
		}
	}
	return false;
}
int dfs(int x, int tot = INF)
{
	if (x == t) return tot;
	int ret = 0;
	for (int i = current[x]; ~i; i = g[i].pre)
	{
		int y = g[i].y, r = g[i].r;
		if (layer[y] == layer[x] + 1 && r > 0)
		{
			current[x] = i;
			int tmp = dfs(y, min(r, tot - ret));
			g[i].r -= tmp;
			g[i ^ 1].r += tmp;
			ret += tmp;
			if (ret == tot) return ret;
		}
	}
	layer[x] = -1;
	return ret;
}
int solve(int sz = N)
{
	int ret = 0;
	while (bfs(sz))
	{
		memcpy(current, g.top, sizeof(int)*sz);
		ret += dfs(s);
	}
	return ret;
}

int in[301];
int out[301];
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
		s = 0, t = n + 1;
		MEM(in, 0);
		MEM(out, 0);
		g.init(t + 1);
		while (m--)
		{
			int x, y, w;
			scanf("%d%d%d", &x, &y, &w);
			if (x == y) continue;
			in[y]++;
			out[x]++;
			if (w == 0)
				g.addEdge(x, y, 1);
		}
		int flag = 1;
		for (int i = 1; i <= n; i++)
		{
			if ((in[i] + out[i]) & 1) flag = 0;
		}
		if (flag == 0)
		{
			printf("impossible\n");
			continue;
		}
		int sum = 0;
		for (int i = 1; i <= n; i++)
		{
			sum += abs(in[i] - out[i]);
			if (out[i] - in[i] > 0) g.addEdge(s, i, (out[i] - in[i]) / 2);
			else g.addEdge(i, t, (in[i] - out[i]) / 2);
		}
		if (solve(t + 1) == sum / 4) printf("possible\n");
		else printf("impossible\n");

	}
	return 0;
}