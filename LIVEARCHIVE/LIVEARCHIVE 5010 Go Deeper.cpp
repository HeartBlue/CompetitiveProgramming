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
const int N = 1e4 + 10;
vector<int> v[N];
int low[N], dfn[N];
int in[N], top, s[N];
int belong[N];
int cnt;
int scccnt;
pair<int, int> p[N];
void tarjan(int x)
{
	dfn[x] = low[x] = ++cnt;
	in[x] = 1;
	s[top++] = x;
	for (auto &y : v[x])
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
			belong[y] = scccnt;
			in[y] = 0;
			if (y == x) break;
		}
	}
}
void init(int n)
{
	memset(dfn, 0, sizeof(int)*n);
	memset(in, 0, sizeof(int)*n);
	cnt = scccnt = 0;
	top = 0;
	for (int i = 0; i < n; i++)
	{
		if (!dfn[i])
			tarjan(i);
	}
}
int a[N], b[N], c[N];
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
		for (int i = 0; i < m; i++) scanf("%d%d%d", &a[i], &b[i], &c[i]);
		int l = 0, r = m;
		int ans = 0;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			for (int i = 0; i < 2 * n; i++) v[i].clear();
			for (int i = 0; i < mid; i++)
			{
				int x = a[i] << 1;
				int y = b[i] << 1;
				if (c[i] == 0)
				{
					v[x ^ 1].push_back(y);
					v[y ^ 1].push_back(x);
				}
				else if (c[i] == 1)
				{
					v[x].push_back(y);
					v[y ^ 1].push_back(x ^ 1);
					v[y].push_back(x);
					v[x ^ 1].push_back(y ^ 1);
				}
				else if (c[i] == 2)
				{
					v[x].push_back(y ^ 1);
					v[y].push_back(x ^ 1);
				}
			}
			int flag = 1;
			init(2 * n);
			for (int i = 0; i < 2 * n; i += 2)
			{
				if (belong[i] == belong[i ^ 1])
				{
					flag = 0;
					break;
				}
			}
			if (flag) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}