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
#define N (int)1e3
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

dat A[M+5];
vector <vector <set <int> >> B;
vector <vector <int>> C;
int t, n, m, q;

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin >> t;
	while(t--){
		cin >> n >> m >> q;
		bool sw = (n > m);
		if(sw) swap(n, m);

		B.resize(n+1);
		C.resize(n+1);

		for(int i=1; i<=n; i++){
			B[i].resize(m+2);
			C[i].resize(m+2);
		}

		for(int i=1; i<=n; i++){
			for(int j=1; j<=m+1; j++){
				B[i][j].clear();
				C[i][j] = 0;
			}
		}

		for(int i=1; i<=q; i++){
			cin >> A[i].x >> A[i].y >> A[i].c;
			A[i].x++;
			A[i].y++;
			if(sw) swap(A[i].x, A[i].y);

			//cout << "EQ: " << i << "\n";
			for(int j=max(1LL, A[i].x-A[i].c); j<=min(n, A[i].x + A[i].c); j++){
				int d = floor(sqrt(A[i].c*A[i].c - (A[i].x - j) * (A[i].x - j)));
				B[j][max(1LL, A[i].y - d)].insert(-i);
				B[j][min(m+1, A[i].y + d + 1)].insert(i);
				//cout << "d: " << d << ", j: " << j << ", ins: " << A[i].y - d << ", pop: " << A[i].y + d + 1 << "\n"; 
			}
		}

		for(int i=1; i<=n; i++){
			set <int> s;
			for(int j=1; j<=m; j++){
				for(auto u: B[i][j]){
					if(u < 0) s.insert(-u);
					else s.erase(u);
				}
				if(s.empty()) continue;
				int k = *s.rbegin();
				C[i][j] = A[k].c*A[k].c - ((i - A[k].x) * (i - A[k].x) + (j - A[k].y) * (j - A[k].y)) + 1;
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