#include <bits/stdc++.h>
using namespace std;
#define int long long
vector<pair<int, int>> adj[2005][2005];
char ca[2005][2005];
bool vis[2005][2005];
int dsu[2005][2005], dsua[2005][2005], sima, simb;
/*
pair<int, int> par(int a, int b) {
	if(dsu[a][b] == a && dsua[a][b] == b) {
		return {a, b};
	} else {
		int c = dsu[a][b], d = dsua[a][b];
		pair<int, int> e = par(c, d);
		dsu[a][b] = e.first;
		dsua[a][b] = e.second;
	}
}

void konek(int a, int b, int c, int d) {
	pair<int, int> e = par(a, b), f = par(c, d);
	if(e != f) {
		dsu[f.first][f.second] = e.first;
		dsua[f.first][f.second] = e.second;
	}
	
}*/

void dfs(int a, int b) {
	vis[a][b] = true;
	dsu[a][b] = sima;
	dsua[a][b] = simb;
	for(int i = 0; i < adj[a][b].size(); i++) {
		int c = adj[a][b][i].first, d = adj[a][b][i].second;
		if(vis[c][d]) continue;
		
		dfs(c, d);
	}
}

signed main() {
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int t;
	cin >> t;
	while(t--) {
		int n, m, q;
		cin >> n >> m >> q;
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				cin >> ca[i][j];
				adj[i][j].clear();
				dsu[i][j] = i;
				dsua[i][j] = j;
				vis[i][j] = false;
			}
		}
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				for(int ii = i - 1; ii <= i + 1; ii++) {
					for(int jj = j - 1; jj <= j + 1; jj++) {
						if(ii < 1 || ii > n || jj < 1 || jj > m || abs(i + j - ii - jj) != 1) continue;
						int tot = 0;
						if(ca[i][j] == 'B' || ca[ii][jj] == 'B') tot++;
						if(ca[i][j] == 'R' || ca[ii][jj] == 'R') tot++;
						if(tot != 2) adj[i][j].push_back({ii, jj});
					}
				}
			}
		}
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				if(vis[i][j]) continue;
				sima = i;
				simb = j;
				
				dfs(i, j);
			}
		}
		while(q--) {
			int a, b, c, d;
			cin >> a >> b >> c >> d;
			a++;
			b++;
			c++;
			d++;
			//cout << dsu[a][b] << " " << dsua[a][b] << " " << dsu[c][d] << " " << dsua[c][d] << "\n";
			if(dsu[a][b] == dsu[c][d] && dsua[a][b] == dsua[c][d]) {
				cout << "YES" << "\n";
			} else {
				cout << "NO" << "\n";
			}
			
		}
	}
	
}

