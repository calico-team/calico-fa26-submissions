#if defined(__GNUC__) && defined(__has_include) && __has_include(<bits/allocator.h>)
#include <bits/allocator.h>
#endif

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#endif

#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>
#include <iostream>
#include <iterator>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <ctime>
#include <cstring>
#include <chrono>
using namespace std;
#define pb push_back
#define ppb pop_back
#define pi 3.1415926535897932384626433832795028841971
#define mp make_pair
#define x first
#define y second
#define pii pair<int,int>
#define pdd pair<double,double>
#define INF 1000000000
#define FOR(i,a,b) for (int _n(b), i(a); i <= _n; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b);i>=_b;i--)
#define all(c) (c).begin(), (c).end()
#define SORT(c) sort(all(c))
#define rep(i,n) FOR(i,1,(n))
#define rept(i,n) FOR(i,0,(n)-1)
#define L(s) (int)((s).size())
#define C(a) memset((a),0,sizeof(a))
#define VI vector <int>
#define ll long long

int a, b, c, d, n, m, k, kolt;
char str[102];

VI sm[200002];
int pr[200002];
void dfs(int v, int p) {
	pr[v] = p;
	rept(i, L(sm[v])) {
		int w = sm[v][i];
		if (w == p) continue;
		dfs(w, v);
	}
}
void solve_first() {
	scanf("%d", &n);
	rept(i, n - 1) {
		scanf("%d%d", &a, &b); --a; --b;
		sm[a].pb(b);
		sm[b].pb(a);
	}
	dfs(0, -1);

	int xr = 0;
	rep(i, n - 1) {
		xr ^= pr[i];
	}
	pr[0] = xr;

	rept(i, n) {
		if (i) printf(" ");
		printf("%d", pr[i] + 1);
	}
	printf("\n");
}

void solve_second() {
	scanf("%d", &n);

	int v = -1;
	rept(i, n) {
		scanf("%d", &pr[i]);
		if (pr[i] != -1) {
			--pr[i];
		} else {
			v = i;
		}
	}

	if (v != 0) {
		int xr = 0;
		rept(i, n) {
			if (pr[i] != -1) xr ^= pr[i];
		}
		pr[v] = xr;
		pr[0] = -1;
	}

	rep(i, n - 1) {
		printf("%d %d\n", i + 1, pr[i] + 1);
	}
}
int main() {
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);

	scanf("%s", str);

	if (str[0] == 'F') {
		solve_first();
	} else {
		solve_second();
	}
}
