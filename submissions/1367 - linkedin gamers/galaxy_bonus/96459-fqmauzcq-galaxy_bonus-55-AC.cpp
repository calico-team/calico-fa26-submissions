#include <bits/stdc++.h> 
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace std; 
   
using str = string; 
using ll = long long; 
using ld = long double; 
   
#define int long long 
#define show(x) cerr << (#x) << " = " << (x) << '\n'; 
#define output_vector(v) for(auto &x : v){cout << x << " ";}cout << '\n'; 
#define output_pairvector(v) for(auto &x : v){cout << x.first << " " << x.second << '\n';} 
#define vt vector 
#define pii pair<int,int> 
#define piii pair<pair<int,int>, pair<int,int>> 
#define discretize(x) sort(x.begin(), x.end()); x.erase(unique(x.begin(), x.end()), x.end()); 
#define all(x) x.begin(), x.end() 
#define rall(x) x.rbegin(), x.rend() 
#define sz(x) ll(x.size()) 
#define fir first 
#define sec second 

const int mod = 998244353;
const int INF = 1e15;
const int maxn = 5000;
int n, m;

bool valid_pair(int r, int c) {
	if(r >= 0 && r < n && c >= 0 && c < m) {
		return true;
	} else {
		return false;
	}
}

vector<str> grid;
vector<pii> d = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int vis[205][205];
 
int cnt = 1;
void bfs(int i, int j) {
	queue<pii> q;
	q.push({i, j});
	vis[i][j] = cnt;
	while(!q.empty()) {
		int r = q.front().fir;
		int c = q.front().sec;
		//show(r);
		q.pop();
		for(auto &[dx, dy] : d) {
			if(!valid_pair(r+dx, c+dy)) continue;
			if(vis[r+dx][c+dy]) continue;
			char next_cell = grid[r+dx][c+dy];
			char curr_cell = grid[r][c];
			//show(next_cell);
			if(next_cell == curr_cell || curr_cell == '.' || next_cell == '.') {
				vis[r+dx][c+dy] = cnt;
				q.push({r+dx, c+dy});
			}
		}
	}
}

void solve() {
	int queries;
	cin >> n >> m >> queries;
	grid.resize(n, "");
	for(int i=0; i<n; ++i) {
		cin >> grid[i];
	}
	memset(vis, 0, sizeof(vis));
	for(int i=0; i<n; ++i) {
		for(int j=0; j<m; ++j) {
			if(!vis[i][j]) {
				bfs(i, j);
				cnt++;
			}
		}
	}
	//show(vis[1][3]);
	while(queries--) {
		int rs, cs, re, ce;
		cin >> rs >> cs >> re >> ce;
		if(vis[rs][cs] == vis[re][ce]) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc = 1;
    cin >> tc;

    while(tc--) {
		solve();
	}
}
