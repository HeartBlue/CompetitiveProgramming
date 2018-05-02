/*
learn to solve 2-sat
2-sat + binary-search
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
void init(int n)
{
	memset(in, 0, sizeof(int)*n);
	memset(dfn, 0, sizeof(int)*n);
	top = cnt = scccnt = 0;
	for (int i = 0; i < n; i++)
	{
		if (!dfn[i])
			tarjan(i);
	}
}
int pos[N];
pair<int, int> p[N];
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF)
	{
		if (n == 0 && m == 0) break;
		for (int i = 0; i < 2 * n; i++)
		{
			int x;
			scanf("%d", &x);
			pos[x] = i;
		}
		for (int i = 0; i < m; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			p[i] = make_pair(pos[x], pos[y]);
		}
		int ret = 0;
		int l = 1, r = m;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			for (int i = 0; i < 2 * n; i++) v[i].clear();
			for (int i = 0; i < mid; i++)
			{
				int x = p[i].first;
				int y = p[i].second;
				v[x].push_back(y ^ 1);
				v[y].push_back(x ^ 1);
			}
			init(n * 2);
			int flag = 1;
			for (int i = 0; i < 2 * n; i += 2)
			{
				if (belong[i] == belong[i ^ 1])
				{
					flag = 0;
					break;
				}
			}
			if (flag) ret = mid, l = mid + 1;
			else r = mid - 1;
		}
		printf("%d\n", ret);
	}
	return 0;
}