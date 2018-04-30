/*
Mincut on Undircted Graph

learn to use Stoer_Wagner Algorithm

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
const int N = 3e2 + 10;
int a[N][N];
int bin[N];
int vis[N];
int dis[N];
int n, m;
int contract(int &s, int &t)
{
	MEM(vis, 0);
	MEM(dis, 0);
	int ret = 0;
	while (1)
	{
		int k = -1;
		int maxv = -1;
		for (int i = 1; i <= n; i++)
		{
			if (vis[i] || bin[i]) continue;
			if (maxv < dis[i]) maxv = dis[i], k = i;
		}
		if (k == -1) break;
		vis[k] = 1;
		ret = maxv;
		s = t;
		t = k;
		for (int i = 1; i <= n; i++)
		{
			if (vis[i] || bin[i]) continue;
			dis[i] += a[k][i];
		}
	}
	return ret;
}
int Stoer_Wagner()
{
	int s, t;
	int ret = INF;
	MEM(bin, 0);
	for (int i = 1; i < n; i++)
	{
		int res = contract(s, t);
		if (res == 0) return 0;
		ret = min(ret, res);
		for (int j = 1; j <= n; j++)
		{
			if (bin[j]) continue;
			a[s][j] += a[t][j];
			a[j][s] += a[j][t];
		}
		bin[t] = 1;
	}
	return ret;
}
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int s;
	while (scanf("%d%d%d", &n, &m, &s) != EOF)
	{
		if (n == 0 && m == 0 && s == 0) break;
		MEM(a, 0);
		while (m--)
		{
			int x, y, w;
			scanf("%d%d%d", &x, &y, &w);
			a[x][y] += w;
			a[y][x] += w;
		}
		printf("%d\n", Stoer_Wagner());
	}
	return 0;
}