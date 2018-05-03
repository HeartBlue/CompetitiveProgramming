/*
learn to solve 2-sat
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
vector<int> v[N];
int low[N], dfn[N];
int in[N], top, s[N];
int belong[N];
int cnt;
int scccnt;
void tarjan(int x)
{
	dfn[x] = low[x] = ++cnt;
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
class Segment
{
public:
	int l, r;
	Segment(int j = 0, int r = 0)
	{
		this->l = l;
		this->r = r;
	}
	bool in(int x)
	{
		return x > l && x < r;
	}
	bool out(int x)
	{
		return x < l || x > r;
	}
	bool check(Segment &s)
	{
		if (in(s.l) && out(s.r)) return true;
		if (in(s.r) && out(s.l)) return true;
		return false;
	}
} seg[N];
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF)
	{
		for (int i = 0; i < m; i++)
		{
			scanf("%d%d", &seg[i].l, &seg[i].r);
			if (seg[i].l > seg[i].r) swap(seg[i].l, seg[i].r);
		}
		for (int i = 0; i < 2 * m; i++) v[i].clear();
		for (int i = 0; i < m; i++)
		{
			for (int j = i + 1; j < m; j++)
			{
				if (seg[i].check(seg[j]))
				{
					v[i << 1].push_back(j << 1 | 1);
					v[j << 1].push_back(i << 1 | 1);
					v[i << 1 | 1].push_back(j << 1);
					v[j << 1 | 1].push_back(i << 1);
				}
			}
		}
		init(2 * m);
		int flag = 1;
		for (int i = 0; i < 2 * m; i++)
		{
			if (belong[i] == belong[i ^ 1])
			{
				flag = 0;
				break;
			}
		}
		if (flag) puts("panda is telling the truth...");
		else puts("the evil panda is lying again");
	}
	return 0;
}