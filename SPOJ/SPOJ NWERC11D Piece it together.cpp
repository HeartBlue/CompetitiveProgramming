/*
given a n*m board with only 'W' or 'B' or '.' on it.
check whether one can use several 
"{
BW
W
}"
which can be rotated to fill the board.
make all the 'B' to two, one connect vertical neighbour 'W', the other horizontal. 
then max-flow
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
const int N = 1e6 + 10;
const int M = 1e6 + 10;
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
int dx[] = { 0,0,-1,1 };
int dy[] = { 1,-1,0,0 };
char c[510][510];
int id[510][510];
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int ncase;
	scanf("%d", &ncase);
	while (ncase--)
	{
		int n, m;
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) scanf("%s", c[i] + 1);
		int cur = 1;
		int totb = 0;
		int totw = 0;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				if (c[i][j] == '.') continue;
				id[i][j] = cur++;
				if (c[i][j] == 'W') totw++;
				if (c[i][j] == 'B') cur++, totb++;
			}
		}
		if (totb * 2 != totw)
		{
			puts("NO");
			continue;
		}
		s = 0, t = cur;
		g.init(t + 1);
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				if (c[i][j] == 'B')
				{
					g.addEdge(s, id[i][j], 1);
					g.addEdge(s, id[i][j] + 1, 1);
					for (int o = 0; o < 4; o++)
					{
						int x = i + dx[o];
						int y = j + dy[o];
						if (x < 1 || x > n) continue;
						if (y < 1 || y > m) continue;
						if (c[x][y] != 'W') continue;
						g.addEdge(id[i][j] + o / 2, id[x][y], 1);
					}
				}
				if (c[i][j] == 'W')
				{
					g.addEdge(id[i][j], t, 1);
				}
			}
		}
		if (solve(t + 1) == totb * 2) puts("YES");
		else puts("NO");
	}
	return 0;
}