/*
dp
Knuth Optimization
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
const int N = 5E3 + 10;
LL dp[N][N];
LL s[N][N];
int cost[N][N];
int a[N];
int main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	int ncase;
	scanf("%d", &ncase);
	while (ncase--)
	{
		int n, k;
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; i++)
		{
			scanf("%d", &a[i]);
		}
		for (int i = 1; i <= n; i++)
		{
			for (int j = i; j <= n; j++)
			{
				cost[i][j] = cost[i][j - 1] | a[j];
			}
		}
		for (int i = 1; i <= n; i++) dp[i][i] = dp[i - 1][i - 1] + a[i];
		for (int i = 1; i <= n; i++) s[i][i] = i;
		for (int i = 1; i <= n; i++)
		{
			for (int l = 1; l + i <= n; l++)
			{
				int r = i + l;
				dp[l][r] = 0;
				int L = s[l][r - 1];
				int R = s[l + 1][r];
				for (int k = L; k <= R; k++)
				{
					if (dp[l][r] < dp[l - 1][k - 1] + cost[k][r])
					{
						dp[l][r] = dp[l - 1][k - 1] + cost[k][r];
						s[l][r] = k;
					}
				}
			}
		}
		printf("%lld\n", dp[k][n]);
	}
	return 0;
}