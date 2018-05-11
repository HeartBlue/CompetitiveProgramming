/*
fractal.
It's really hard for me to code a simple geometry problem. 
Just dfs 500 steps, with prune.
If the current part is all in the rectangle, then add all the part to the answer.
If the current part is outside of the rectangle, do not continues.
*/
#line 5 "FractalPicture.cpp"  
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
double eps = 1e-12;
int cmp(double x)
{
	if (abs(x) < eps) return 0;
	return x > 0 ? 1 : -1;
}
class Rect
{
public:
	double x1, y1, x2, y2;
	Rect(double x1 = 0, double y1 = 0, double x2 = 0, double y2 = 0)
	{
		this->x1 = x1;
		this->x2 = x2;
		this->y1 = y1;
		this->y2 = y2;
	}
	double getLength(Rect r)
	{
		double ax = max(x1, min(r.x1, r.x2));
		double bx = min(x2, max(r.x1, r.x2));
		double ay = max(y1, min(r.y1, r.y2));
		double by = min(y2, max(r.y1, r.y2));
		if (cmp(ax - bx) > 0 || cmp(ay - by) > 0) return 0;
		return bx - ax + by - ay;
	}
	double check(Rect r)
	{
		double ax = max(x1, min(r.x1, r.x2));
		double bx = min(x2, max(r.x1, r.x2));
		double ay = max(y1, min(r.y1, r.y2));
		double by = min(y2, max(r.y1, r.y2));
		if (cmp(ax - bx) > 0 || cmp(ay - by) > 0) return 0;
		return cmp(bx - ax)*cmp(by - ay);
	}
	bool contain(Rect r)
	{
		if (cmp(x1 - r.x1) > 0) return false;
		if (cmp(x2 - r.x2) < 0) return false;
		if (cmp(y1 - r.y1) > 0) return false;
		if (cmp(y2 - r.y2) < 0) return false;
		return true;
	}
	Rect refrain()
	{
		if (cmp(x1 - x2) == 0)
		{
			double len = abs(y2 - y1) / 3;
			return Rect(x1 - len, min(y1, y2), x1 + len, max(y1, y2));
		}
		else
		{
			double len = abs(x2 - x1) / 3;
			return Rect(min(x1, x2), y1 - len, max(x1, x2), y1 + len);
		}
	}
	double size()
	{
		return abs(x1 - x2)*abs(y1 - y2);
	}
	Rect getfirst()
	{
		double x, y;
		if (cmp(x1 - x2) == 0)
		{
			x = x1;
			y = y1 + (y2 - y1) / 3 * 2;
		}
		else
		{
			x = x1 + (x2 - x1) / 3 * 2;
			y = y1;
		}
		return Rect(x1, y1, x, y);
	}
	vector<Rect> getLine()
	{
		vector<Rect> vt;
		if (cmp(x1 - x2) == 0)
		{
			double x = x1;
			double y = y1 + (y2 - y1) / 3 * 2;
			double len = abs(y2 - y1) / 3;
			vt.push_back(Rect(x, y, x, y2));
			vt.push_back(Rect(x, y, x - len, y));
			vt.push_back(Rect(x, y, x + len, y));
		}
		else
		{
			double x = x1 + (x2 - x1) / 3 * 2;
			double y = y1;
			double len = abs(x2 - x1) / 3;
			vt.push_back(Rect(x, y, x2, y));
			vt.push_back(Rect(x, y, x, y - len));
			vt.push_back(Rect(x, y, x, y + len));
		}
		return vt;
	}
} r;
double dfs(Rect line, int tot = 499)
{
	if (tot == 0)
	{
		return r.getLength(line);
	}
	auto tmp = line.refrain();
	if (tmp.check(r) == 0) 
		return 0;
	if (r.contain(tmp))
	{
		double len = r.getLength(line);
		return len / 3 * 2 * (tot + 1) + len / 3;
	}
	double ret = r.getLength(line.getfirst());
	auto v = line.getLine();
	for (auto &o : v)
	{
		ret += dfs(o, tot - 1);
	}
	return ret;
}
class FractalPicture
{
public:
	double getLength(int x1, int y1, int x2, int y2)
	{
		//$CARETPOSITION$  
		r = Rect(x1, y1, x2, y2);
		return dfs(Rect(0, 0, 0, 81));
	}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
