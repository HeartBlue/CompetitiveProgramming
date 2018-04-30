/*
Given a DAG, you need add some value to some edges, so that each route from 1 to n is same. 

And for every route from 1 to n, you can only modified at most one edge.

Very soon, I got the idea, I need make two patitions, one belong to node 1 and the other belong to node n.

But failed to find a correct strategy for 4 hours.

At last, I google the solution and got AC.

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
vector<tuple<int, int, int>> v1[N], v2[N];
int dis1[N];
int dis2[N];
int dis3[N];
int dis4[N];
int belong[N];
int deg[N];
int vis[N];
int ans[N];
int n, m;
void checks()
{
	for (int i = 1; i <= n; i++) deg[i] = v2[i].size();
	memset(dis1, 0, sizeof(int)*(n + 1));
	memset(dis2, 0x3f, sizeof(int)*(n + 1));
	dis1[1] = 0;
	dis2[1] = 0;
	queue<int> q;
	q.push(1);
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		for (auto &p : v1[x])
		{
			int w, y, pos;
			tie(w, y, pos) = p;
			deg[y]--;
			dis1[y] = max(dis1[y], dis1[x] + w);
			dis2[y] = min(dis2[y], dis2[x] + w);
			if (deg[y] == 0) q.push(y);
		}
	}
}
void checkt()
{
	for (int i = 1; i <= n; i++) deg[i] = v1[i].size();
	memset(dis3, 0, sizeof(int)*(n + 1));
	memset(dis4, 0x3f, sizeof(int)*(n + 1));
	dis3[n] = 0;
	dis4[n] = 0;
	queue<int> q;
	q.push(n);
	while (!q.empty())
	{
		int x = q.front();
		q.pop();
		for (auto &p : v2[x])
		{
			int w, y, pos;
			tie(w, y, pos) = p;
			deg[y]--;
			dis3[y] = max(dis3[y], dis3[x] + w);
			dis4[y] = min(dis4[y], dis4[x] + w);
			if (deg[y] == 0) q.push(y);
		}
	}
}
int refrain()
{
	memset(belong, 0, (n + 1) * sizeof(int));
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		if (dis1[i] == dis2[i]) belong[i] = 1;
		if (dis3[i] == dis4[i]) belong[i] = n;
		if (belong[i] != 0) cnt++;
	}
	return cnt;
}
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int ks = 1;
	while (scanf("%d%d", &n, &m) != EOF)
	{
		if (n == 0 && m == 0) break;
		memset(belong, 0, sizeof(int)*(n + 1));
		for (int i = 1; i <= n; i++) v1[i].clear();
		for (int i = 1; i <= n; i++) v2[i].clear();
		for (int i = 1; i <= m; i++)
		{
			int x, y, w;
			scanf("%d%d%d", &x, &y, &w);
			v1[x].push_back({ w,y,i });
			v2[y].push_back({ w,x,i });
		}
		checks();
		checkt();
		int sum = refrain();
		if (sum < n)
		{
			printf("Case %d: No solution\n", ks++);
			continue;
		}
		memset(ans, 0, sizeof(int)*(m + 1));
		int tot = 0;
		for (int i = 1; i <= n; i++)
		{
			if (belong[i] != 1) continue;
			for (auto &p : v1[i])
			{
				int w, y, pos;
				tie(w, y, pos) = p;
				if (belong[y] != n) continue;
				ans[pos] = dis1[n] - dis3[y] - dis1[i] - w;
				if (ans[pos] > 0) tot++;
			}
		}
		printf("Case %d: %d %d\n", ks++, tot, dis1[n]);
		for (int i = 1; i <= m; i++)
		{
			if (ans[i] == 0) continue;
			printf("%d %d\n", i, ans[i]);
		}
	}
	return 0;
}