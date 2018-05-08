/*
using dsu instead of 2-sat
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
const int N = 4e5 + 10;
class UnionFind
{
public:
	int p[N];
	void init(int n = N)
	{
		memset(p, -1, sizeof(int)*n);
	}
	int treesize(int x)
	{
		return -p[Find(x)];
	}
	int Find(int x)
	{
		int s = x;
		while (p[s] >= 0) s = p[s];
		while (x != s)
		{
			int t = p[x];
			p[x] = s;
			x = t;
		}
		return s;
	}
	void Union(int x, int y)
	{
		int px = Find(x);
		int py = Find(y);
		if (p[px] > p[py]) swap(px, py);
		p[px] += p[py];
		p[py] = px;
	}
} uf;
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n;
	cin >> n;
	LL x, y, o1, o2;
	int flag = 0;
	int k1 = 0;
	int k2 = n * 2;
	map<LL, int> m1, m2;
	uf.init();
	for (int i = 0; i < n; i++)
	{
		if (flag)
		{
			puts("No");
			continue;
		}
		cin >> x >> y >> o1 >> o2;
		if (!m1.count(x))
		{
			m1[x] = k1;
			k1 += 2;
		}
		if (!m2.count(y))
		{
			m2[y] = k2;
			k2 += 2;
		}
		x = m1[x];
		y = m2[y];
		if (o1 != o2) x ^= 1;
		if (uf.Find(x) == uf.Find(y ^ 1) || uf.Find(x ^ 1) == uf.Find(y))
		{
			puts("No");
			flag = 1;
			continue;
		}
		puts("Yes");
		if (uf.Find(x) != uf.Find(y)) uf.Union(x, y);
		if (uf.Find(x ^ 1) != uf.Find(y ^ 1)) uf.Union(x ^ 1, y ^ 1);
	}
	return 0;
}