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

VI sm[10002];
int pr[10002];
int ds[10002];
int cnt[10002], took[10002];
int main() {
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	scanf("%d", &kolt);
	rep(hod, kolt) {
		scanf("%d%d%d", &n, &m, &k);

		rept(i, n) sm[i].clear(), ds[i] = INF;
		rept(i, n + 1) cnt[i] = 0, took[i] = 0;
		queue<int> q;

		rept(i, n) {
			scanf("%d", &pr[i]); --pr[i];
			if (pr[i] != -1) {
				sm[pr[i]].pb(i);
			} else {
				ds[i] = 0;
				q.push(i);
			}
		}
		
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			rept(i, L(sm[v])) {
				int w = sm[v][i];
				if (ds[w] > ds[v] + 1) {
					ds[w] = ds[v] + 1;
					q.push(w);
				}
			}
		}

		rept(i, n) {
			++cnt[ds[i]];
		}

		int p = 0;
		int ans = 0;
		int last = 0;

		int lim = min(1000, n);
		rept(i, m) {

			int st = min(lim, last + 1);
			int need = k;
			FORD(i, st, 0) {
				if (!cnt[i]) continue;
				if (i && !took[i - 1]) continue;

				int can = min(cnt[i] - took[i], i ? (took[i - 1] == cnt[i - 1] ? INF : took[i - 1]) : INF);
				can = min(can, need);

				need -= can;
				took[i] += can;
				ans += can;
				last = max(last, i);
			}
		}
		printf("%d\n", ans);
	}
}
