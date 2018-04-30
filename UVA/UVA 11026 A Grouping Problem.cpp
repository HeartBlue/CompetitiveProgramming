/*
simple dp

give n numbers, 
f(i) = sigma(product of group with size i) % mod;
you should give the maximum of f(i)

dp[i][j] = (a[j] * dp[i - 1][j - 1] + dp[i][j - 1]) % m;

dp[i][j] means the product of the first j numbers with group size i

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
const int N = 1e3 + 10;
LL dp[N][N];
int a[N];
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int n, m;
	while (scanf("%d%d", &n, &m) != EOF)
	{
		if (n == 0 && m == 0) break;
		MEM(dp, 0);
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &a[i]);
		}
		for (int i = 1; i <= n; i++)
		{
			dp[1][i] = (dp[1][i - 1] + a[i]) % m;
		}
		LL ans = dp[1][n];
		for (int i = 2; i <= n; i++)
		{
			for (int j = i; j <= n; j++)
			{
				dp[i][j] = (a[j] * dp[i - 1][j - 1] + dp[i][j - 1]) % m;
			}
			ans = max(ans, dp[i][n]);
		}
		printf("%lld\n", ans);
	}
	return 0;
}