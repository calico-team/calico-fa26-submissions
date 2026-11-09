#include <bits/stdc++.h>
#define pb push_back
#define f first
#define s second

using namespace std;
int r[] = {1, 0, -1, 0}, c[] = {0, 1, 0, -1};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t; while(t--) {
    	int n, m, e; cin >> n >> m >> e; vector<string> v(n);
    	for(int i=0;i<n;i++) cin >> v[i]; vector<vector<int>> w(n,vector<int>(m)); int p = 1;
    	for(int i=0;i<n;i++) for(int j=0;j<m;j++) if(!w[i][j]) {
    		w[i][j] = p;
    		queue<pair<int,int>> q; q.push({i,j});
    		while(!q.empty()) {
    			int x = q.front().f, y = q.front().s; q.pop();
    			for(int k=0;k<4;k++) {
    				if(0 > x+r[k] || x+r[k] >= n || 0 > y+c[k] || y+c[k] >= m) continue;
    				if(w[x+r[k]][y+c[k]] || (int)v[x+r[k]][y+c[k]]+(int)v[x][y] == 148) continue;
    				q.push({x+r[k],y+c[k]}); w[x+r[k]][y+c[k]] = p;
    			}
    		}
    		p++;
    	}
    	while(e--) {int a, b, c, d; cin >> a >> b >> c >> d; cout << (w[a][b] == w[c][d]? "YES\n":"NO\n");}
    }
}
