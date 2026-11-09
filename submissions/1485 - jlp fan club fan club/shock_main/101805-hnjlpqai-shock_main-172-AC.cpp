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

#define M (int)2e4
#define INF (int)1e9
#define INFL (int)1e18
#define MOD (int)(1e9+7)
#define fir first
#define sec second

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

struct dat {
	int x, y, c;
};

class DSU {
	private:
	vector <int> parents, sizes, maxs;
	public:
	   DSU(int num): parents(num), sizes(num, 1), maxs(num){
		   iota(parents.begin(), parents.end(), 0);
		   iota(maxs.begin(), maxs.end(), 0);
	   }
	   int top(int x){ return parents[x] == x ? x : parents[x] = top(parents[x]); }
	   int last(int x){ return maxs[top(x)]; }
	   bool linked(int x, int y){ return top(x) == top(y); }
	   void link(int x, int y){
		   x = top(x);
		   y = top(y);
		   if(x == y) return;
		   if(sizes[x] < sizes[y]) swap(x, y);
		   parents[y] = x;
		   sizes[x] += sizes[y];
		   maxs[x] = max(maxs[x], maxs[y]);
	   }
};

dat A[M+5];
vector <vector <int>> C;
int t, n, m, q;

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin >> t;
	while(t--){
		cin >> n >> m >> q;
		bool sw = (n > m);
		if(sw) swap(n, m);

		C.resize(n+1);
		for(int i=1; i<=n; i++){
			C[i].resize(m+2);
			for(int j=0; j<=m+1; j++) C[i][j] = 0;
		}

		for(int i=1; i<=q; i++){
			cin >> A[i].x >> A[i].y >> A[i].c;
			A[i].x++;
			A[i].y++;
			if(sw) swap(A[i].x, A[i].y);
		}

		DSU D(n*(m+1) + 1);
		for(int i=q; i>=1; i--){
			for(int j=max(1LL, A[i].x - A[i].c); j<=min(n, A[i].x + A[i].c); j++){
				int d = sqrt(A[i].c*A[i].c - (A[i].x - j) * (A[i].x - j));
				int l = max(1LL, A[i].y - d), r = min(m, A[i].y + d);
				if(l > r) continue;
				int idx = (j-1)*(m+1);
				for(int k = D.last(idx + l)-idx; k <= r; k = D.last(idx + k) - idx){
					C[j][k] = A[i].c*A[i].c - ( (A[i].x - j)*(A[i].x - j) + (A[i].y - k)*(A[i].y - k) ) + 1;
					D.link(idx + k, idx + k + 1);
				}
			}
		}

		if(!sw){
			for(int i=1; i<=n; i++){
				for(int j=1; j<=m; j++) cout << C[i][j] << " ";
				cout << "\n";
			}
		} else {
			for(int i=1; i<=m; i++){
				for(int j=1; j<=n; j++) cout << C[j][i] << " ";
				cout << "\n";
			}
		}
	}
	return 0;
}