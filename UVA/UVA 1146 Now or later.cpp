/*
learn to solve 2-sat. plus binary-search
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
vector<int> v1[N];
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
bool solve(int n)
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
			return false;
		}
	}
	return true;
}
int a[N][2];
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n;
	while (scanf("%d", &n) != EOF)
	{
		for (int i = 0; i < n; i++)
		{
			scanf("%d%d", &a[i][0], &a[i][1]);
		}
		int l = 0, r = INF;
		int ans = 0;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			for (int i = 0; i < 2 * n; i++) v1[i].clear();
			for (int i = 0; i < n; i++)
			{
				for (int j = i + 1; j < n; j++)
				{
					for (int o1 = 0; o1 < 2; o1++)
					{
						for (int o2 = 0; o2 < 2; o2++)
						{
							if (abs(a[i][o1] - a[j][o2]) < mid)
							{
								int x = i << 1 | o1;
								int y = j << 1 | o2;
								v1[x].push_back(y ^ 1);
								v1[y].push_back(x ^ 1);
							}
						}
					}
				}
			}
			if (solve(2 * n)) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}