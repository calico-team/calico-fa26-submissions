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

int a, b, c, d, n, m, k, kolt, K;
char tmp[3];

map<int, VI > up, rt;

ll solve(int z) {
	auto upIt = up.find(z);
	auto rtIt = rt.find(z);

	if (upIt == up.end() || rtIt == rt.end()) return 0;

	auto& u = upIt->second;
	auto& r = rtIt->second;

	int cnt = 0;
	rept(i, L(u)) {
		int xu = u[i];
		int p1 = upper_bound(all(r), xu - K) - r.begin();	
		int p2 = upper_bound(all(r), xu) - r.begin();

		cnt += p2 - p1;
	}
	return cnt;
}
int main() {
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	scanf("%d", &kolt);
	rep(hod, kolt) {
		scanf("%d%d", &n, &K);
		up.clear(); rt.clear();
		vector<int> zz;
		rept(i, n) {
			scanf("%d%d%d%s", &a, &b, &c, tmp); --a; --b; --c;

			if (tmp[0] == 'N') {
				up[a + b].pb(a);
			} else {
				rt[a + b].pb(a);
			}
			zz.pb(a + b);
		}

		for (auto& it : up) {
			SORT(it.second);
		}
		for (auto& it : rt) {
			SORT(it.second);
		}

		ll ans = (ll)n * K;
		SORT(zz);
		zz.resize(unique(all(zz)) - zz.begin());

		for (auto z : zz) {
			ll cur = solve(z);
			ans -= cur;
		}

		printf("%lld\n", ans);
	}
}
