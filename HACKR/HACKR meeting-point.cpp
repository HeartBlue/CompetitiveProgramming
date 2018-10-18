/*
transformation from manhattan-distance to Chebishev-distance
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
#include <random>
#include <cassert>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
#define MEM(a,b) memset((a),(b),sizeof(a))
const LL INF = 1e9 + 7;
const int N = 2e5 + 10;
LL ans[N];
void solve(vector<pair<int, int>> &vp)
{
	sort(vp.begin(), vp.end());
	int n = vp.size();
	priority_queue<int, vector<int>, greater<int>> pq;
	LL tot0 = 0, tot1 = 0;
	for (auto &p : vp)
	{
		tot1 += p.first;
		pq.push(p.first);
	}
	for (auto &p : vp)
	{
		while (!pq.empty() && pq.top() <= p.first)
		{
			tot1 -= pq.top();
			tot0 += pq.top();
			pq.pop();
		}
		LL &res = ans[p.second];
		int sz = pq.size();
		res += tot1 - 1LL * sz * p.first + 1LL * (n - sz)*p.first - tot0;
	}
}
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n;
	cin >> n;
	vector<pair<int, int>> v1, v2;
	for (int i = 1; i <= n; i++)
	{
		int a, b;
		cin >> a >> b;
		v1.push_back({ a + b,i });
		v2.push_back({ a - b,i });
	}
	solve(v1);
	solve(v2);
	LL ans = INF * INF * 4;
	for (int i = 1; i <= n; i++) ans = min(ans, ::ans[i]);
	printf("%lld\n", ans/2);
	return 0;
}