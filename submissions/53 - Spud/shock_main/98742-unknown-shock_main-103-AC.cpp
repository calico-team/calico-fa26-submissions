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
pair<pii, int> quer[20002];

int delta[502][502];

vector<tuple<int, int, int> > pr[1002];
inline int getp(vector<tuple<int, int, int> >& pr, int v) {
	int& p = get<0>(pr[v]);
	if (p == -1) return v;
	return p = getp(pr, p);
}
inline void un(vector<tuple<int, int, int> >& pr, int v, int u) {
	v = getp(pr, v); u = getp(pr, u);
	if (v == u) return;
	
	int r = get<2>(pr[u]);
	
	int& rv = get<1>(pr[v]);
	int& ru = get<1>(pr[u]);
	
	if (rv < ru) {
		get<0>(pr[v]) = u;
	} else {
		if (rv == ru) ++rv;
		get<0>(pr[u]) = v;
		get<2>(pr[v]) = r;
	}
}

int main() {
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	scanf("%d", &kolt);

	rept(p, 502) {
		rept(i, p + 1) {
			int r = 600;
			int c = 600;

			int ri = r - i;
			int ci = c;

			auto cc = [r, c](int ri, int ci) {
				return (ll)(r - ri) * (r - ri) + (ll)(c - ci) * (c - ci);
			};
			while (cc(ri, ci + 1) <= p * p) ++ci;

			delta[p][i] = ci - c;
		}
	}

	rep(hod, kolt) {
		scanf("%d%d%d", &n, &m, &k);
		bool sw = 0;

		if (n > m) {
			swap(n, m);
			sw = 1;
		}

		rept(i, k) {
			scanf("%d%d%d", &a, &b, &c);
			if (sw) swap(a, b);
			quer[i] = mp(mp(a, b), c);
		}
		vector<VI> res(n, VI(m, 0));

		rept(i, n) {
			pr[i].resize(m + 1);
			rept(j, m + 1) pr[i][j] = make_tuple(-1, 0, j);
		}

		/*un(pr[4], 3, 4);
		un(pr[4], 0, 1);
		un(pr[4], 1, 2);
		//un(pr[4], 2, 3);
		auto o = getp(pr[4], 3);
		cerr << get<2>(pr[4][o]) << endl;
		
		o = getp(pr[4], 2);
		cerr << get<2>(pr[4][o]) << endl;
		exit(0);*/
		
		FORD(h, k - 1, 0) {
			int r = quer[h].x.x;
			int c = quer[h].x.y;
			int p = quer[h].y;

			ll pp = (ll)p * p;

			auto gd = [r, c](int ri, int ci) {
				return (ll)(r - ri) * (r - ri) + (ll)(c - ci) * (c - ci);
			};

			FOR(ri, r - p, r + p) {
				int dd = delta[p][abs(ri - r)];
				int lf = c - dd;
				int rt = c + dd;

				if (rt - lf <= 10) {
					FOR(ci, lf, rt) {
						if (res[ri][ci] == 0) {
							res[ri][ci] = pp - gd(ri, ci) + 1;
							un(pr[ri], ci, ci + 1);
						} 
					}
				} else {
					int ci = lf;
					int iter = 0;
					while (ci <= rt) {
						ci = get<2>(pr[ri][getp(pr[ri], ci)]);
						if (ci > rt) break;

						res[ri][ci] = pp - gd(ri, ci) + 1;
						un(pr[ri], ci, ci + 1);
					}	
				}
			}
		}

		if (sw) {
			vector<VI> tmp(m, VI(n, 0));
			rept(i, n) {
				rept(j, m) {
					tmp[j][i] = res[i][j];
				}
			}
			swap(n, m);
			res.swap(tmp);
		}

		rept(i, n) {
			rept(j, m) {
				if (j) printf(" ");
				printf("%d", res[i][j]);
			}
			printf("\n");
		}
	}
}
