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
class Point
{
public:
	int x, y;
	Point(int x = 0, int y = 0)
	{
		this->x = x;
		this->y = y;
	}
	pair<Point, Point> refrain(int o, int r)
	{
		if (o == 0) return make_pair(Point(x - r, x + r), Point(y, y + r * 2));
		else return make_pair(Point(x - r, x + r), Point(y - r * 2, y));
	}
};
bool check(Point &p1, Point &p2)
{
	return max(p1.x, p2.x) < min(p1.y, p2.y);
}
Point p[N];
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int ncase;
	scanf("%d", &ncase);
	while (ncase--)
	{
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
		{
			scanf("%d%d", &p[i].x, &p[i].y);
			p[i].x *= 2;
			p[i].y *= 2;
		}
		int l = 0, r = INF / 2;
		int ans = 0;
		while (l <= r)
		{
			int mid = (l + r) >> 1;
			for (int i = 0; i < 2 * n; i++) v[i].clear();
			for (int i = 0; i < n; i++)
			{
				for (int j = i + 1; j < n; j++)
				{
					pair<Point, Point> p1, p2;
					for (int o1 = 0; o1 < 2; o1++)
					{
						for (int o2 = 0; o2 < 2; o2++)
						{
							p1 = p[i].refrain(o1, mid);
							p2 = p[j].refrain(o2, mid);
							if (check(p1.first, p2.first) && check(p1.second, p2.second))
							{
								//cout << i << ' ' << j << ' ' << o1 << ' ' << o2 << endl;
								int x = i << 1 | o1;
								int y = j << 1 | o2;
								v[x].push_back(y ^ 1);
								v[y].push_back(x ^ 1);
							}
						}
					}
				}
			}
			init(2 * n);
			int flag = 1;
			for (int i = 0; i < 2 * n; i++)
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