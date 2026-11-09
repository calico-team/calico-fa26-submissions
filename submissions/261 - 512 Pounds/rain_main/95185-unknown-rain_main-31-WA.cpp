#include <functional>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <cctype>
#include <vector>
#include <string>
#include <bitset>
#include <cmath>
#include <queue>
#include <stdio.h>
#include <stack>
#include <ctime>
#include <list>
#include <map>
#include <set>
#include <assert.h>
#define REP(i,n) for(int i=0;i<n;i++)
#define TR(i,x) for(auto i=x.begin();i!=x.end();i++)
#define ALL(x) x.begin(),x.end()
#define SORT(x) sort(ALL(x))
#define CLEAR(x) memset(x,0,sizeof(x))
#define FILL(x,c) memset(x,c,sizeof(x))

using namespace std;

const double eps = 1e-8;

#define PB push_back
#define MP make_pair

typedef map<int,int> MII;
typedef map<string,int> MSI;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<long double> VD;
typedef pair<int,int> PII;
typedef long long int64;
typedef long long ll;
typedef unsigned int UI;
typedef long double LD;
typedef unsigned long long ULL;

struct FenwickTree {
  vector<int> a;
  int n;
 
  FenwickTree(int n) : n(n), a(n + 10, 0) {}
 
  void add(int x, int y) {
    ++x;
    while (x < a.size()) {
      a[x] += y;
      x += x & -x;
    }
  }
 
  int get(int x) {
    ++x;
    int ret = 0;
    while (x) {
      ret += a[x];
      x -= x & -x;
    }
    return ret;
  }
 
  int getSum(int l, int r) {
    assert(l <= r);
    return get(r) - get(l - 1);
  }
};

const int N = 200007;

FenwickTree tree(N);


struct Point {
  int x, y, z;
  char dir;
};

void solve(int caseId) {
  int n, units;
  vector<Point> points;
  cin >> n >> units;
  for (int i = 0; i < n; ++i) {
    int x, y, z;
    static char s[10];
    scanf("%d%d%d%s", &x, &y, &z, s);
    points.push_back({x, y, z, s[0]});
  }
  sort(points.begin(), points.end(), [&](const Point& u, const Point& v) {
    if (u.x + u.y != v.x + v.y) {
      return u.x + u.y < v.x + v.y;
    }
    if (u.z != v.z) {
      return u.z > v.z;
    }
    return u.x < v.x;
  });

  // static unordered_map<long long, int> active;

  long long count = 0;
  for (int i = 0; i < n; ) {
    int j = i;
    while (j < n && points[i].x + points[i].y == points[j].x + points[j].y) ++j;
    for (int k = i; k < j; ++k) {
      if (points[k].dir == 'E') {
        count += tree.getSum(points[k].x, min(points[k].x + units - 1, N));
      } else {
        assert(points[k].dir == 'N');
        if (tree.getSum(points[k].x, points[k].x) == 0) {
          tree.add(points[k].x, 1);
        }
      }
    }
    for (int k = i; k < j; ++k) {
      if (points[k].dir == 'N') {
        if (tree.getSum(points[k].x, points[k].x) == 1) {
          tree.add(points[k].x, -1);
        }
      }
    }
    i = j;
  }

  cout << n * (long long) units - count << endl;
}

int main() {
  int cases;
  cin >> cases;
  for (int i = 1; i <= cases; ++i) {
    solve(i);
  }
  return 0;
}