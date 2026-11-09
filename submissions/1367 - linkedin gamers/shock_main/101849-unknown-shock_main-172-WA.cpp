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
const int maxn = 1e6 + 5;

int n, m, queries;

bool valid_pair(int r, int c) {
	if(r >= 0 && r < n && c >= 0 && c < m) {
		return true;
	} else {
		return false;
	}
}
vector<pii> d = {{0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
vector<int> ans[maxn];
vector<int> vis[maxn];

int dist(int p, int ri, int ci, int r, int c) {
	return p*p - ((r-ri) * (r-ri) + (c-ci) * (c-ci)) + 1;
}

void bfs(int i, int j, int p, int ri, int ci) {
	//show(i);
	queue<pii> q;
	q.push({i, j});
	vis[i][j] = true;
	while(!q.empty()) {
		int r = q.front().fir;
		int c = q.front().sec;
		ans[r][c] = dist(p, ri, ci, r, c);
		//show(r);
		q.pop();
		for(auto &[dx, dy] : d) {
			if(!valid_pair(r+dx, c+dy)) continue;
			if(vis[r+dx][c+dy]) continue;
			if(dist(p, ri, ci, r+dx, c+dy) <= 0) continue;
			vis[r+dx][c+dy] = true;
			q.push({r+dx, c+dy});
		}
	}
}

void solve() {
	cin >> n >> m >> queries;
	for(int i=0; i<n; ++i) {
		vis[i].assign(m, 0);
		ans[i].assign(m, 0);
	}
	vector<pair<pii, int>> qry(queries);
	for(int i=0; i<queries; ++i) {
		cin >> qry[i].fir.fir >> qry[i].fir.sec >> qry[i].sec;
	}
	queue<pii> que;
	for(int i=queries-1; i>=0; --i) {
		//show(i);
		int ri = qry[i].fir.fir;
		int ci = qry[i].fir.sec;
		int pi = qry[i].sec;
		for(auto &[dx, dy] : d) {
			if(!valid_pair(ri+dx*pi, ci+dy*pi)) continue;
			if(!vis[ri+dx*pi][ci+dy*pi]) {
				bfs(ri+dx*pi, ci+dy*pi, pi, ri, ci);
			}
		}
	}
	for(int i=0; i<n; ++i) {
		for(int j=0; j<m; ++j)
			cout << ans[i][j] << " ";
		cout << '\n';
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

