/* 
dp
the number of diffent length end with last half of n is only log(n).
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
const LL INF = 1e8 + 7;
const int N = 1e6 + 10;
int step[N];
int sz[20];
int dp[2][N];
int ans[N];
int sum[N];
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int ncase;
	cin >> ncase;
	while (ncase--)
	{
		int n, m;
		cin >> n >> m;
		int o = 0;
		for (int i = 1; i <= n; i++) dp[o][i] = 1;
		for (int k = 1; k < 20; k++)
		{
			sz[k] = 0;
			sum[0] = 0;
			for (int i = 1; i <= n; i++)
			{
				sum[i] = (sum[i - 1] + dp[o][i]) % INF;
				if (i * 2 > n) 
					sz[k] = (sz[k] + dp[o][i]) % INF;
			}
			o ^= 1;
			for (int i = 1; i <= n; i++)
			{
				dp[o][i] = sum[i / 2];
			}
		}
		ans[0] = 1;
		for (int i = 1; i <= m; i++)
		{
			ans[i] = 0;
			for (int j = 1; j < 20 && j <= i; j++)
			{
				ans[i] = (ans[i] + 1LL * ans[i - j] * sz[j]) % INF;
			}
		}
		cout << ans[m] << endl;

	}
	return 0;
}