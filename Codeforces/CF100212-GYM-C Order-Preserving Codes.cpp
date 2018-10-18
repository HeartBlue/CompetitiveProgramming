/*
Basic Quadrilateral inequality.
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
const int N = 2e3 + 10;
LL cnt[N];
LL dp[N][N];
int s[N][N];
string ans;
void solve(int l, int r)
{
	if (l == r)
	{
		puts(ans.c_str());
		return;
	}
	ans.push_back('0');
	solve(l, s[l][r]);
	ans.pop_back();
	ans.push_back('1');
	solve(s[l][r] + 1, r);
	ans.pop_back();
}
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> cnt[i], cnt[i] += cnt[i - 1];
	for (int i = 1; i <= n; i++)
	{
		dp[i][i] = 0;
		s[i][i] = i;
	}
	for (int i = n; i >= 1; i--)
	{
		for (int j = i + 1; j <= n; j++)
		{
			LL tmp = 0x7fffffffffffffffLL;
			int te = -1;
			for (int k = s[i][j - 1]; k <= s[i + 1][j]; k++)
			{
				if (k == j) break;
				if (tmp > dp[i][k] + dp[k + 1][j] + (cnt[j] - cnt[i - 1]))
				{
					tmp = dp[i][k] + dp[k + 1][j] + cnt[j] - cnt[i - 1];
					te = k;
				}
			}
			dp[i][j] = tmp;
			s[i][j] = te;
		}
	}
	solve(1, n);
	return 0;
}