/**
 * Dohun Kim / Genius0412
 * Contest Name: 
 * Problem Name: 
 * Problem Link: 
 * 
 * Idea:
 * 
*/

#include <bits/stdc++.h>
#define int long long

using namespace std;
using pii = pair<int, int>;

#define all(x) begin(x), end(x)
#define pb push_back
#define eb emplace_back

#define M (int)1e5
#define N (int)2e5
#define INF (int)1e9
#define INFL (int)1e18
#define MOD (int)(1e9+7)
#define fir first
#define sec second

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

struct dat{
	int x, y;
};

int t, n, k;
set <int> B[N+5][2];
dat A[M+5];

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin >> t;
	while(t--){
		cin >> n >> k;
		int ans = n*k;

		for(int i=1; i<=n; i++){
			int asdf;
			char c;
			cin >> A[i].x >> A[i].y >> asdf >> c;
			B[A[i].x + A[i].y][c == 'E'].insert(A[i].x);
		}

		for(int i=0; i<=N; i++){
			if(B[i][0].empty() || B[i][1].empty()) continue;

			for(auto u: B[i][1]){
				ans -= distance(B[i][0].upper_bound(u), B[i][0].upper_bound(u+k-1));
			}
		}

		for(int i=0; i<=N; i++){
			B[i][0].clear();
			B[i][1].clear();
		}

		cout << ans << "\n";
	}
	return 0;
}