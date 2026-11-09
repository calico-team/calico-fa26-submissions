#include <bits/stdc++.h>
#define int long long

using namespace std;

int n, m, q;
const int maxn = 205;
char g[maxn][maxn];
int cnt[maxn][maxn];

vector <int> dx; 
vector <int> dy; 

void bfs(int x, int y, int id){
	queue < pair<int, int> > q;
	q.push({x, y});
	cnt[x][y] = id;
	
	while(!q.empty()){
		int curx = q.front().first;
		int cury = q.front().second;
		q.pop();
		
		for (int i = 0; i < 4; i++){
			int newx = curx + dx[i];
			int newy = cury + dy[i];
			
			if (newx < 0 or newx >= n or newy < 0 or newy >= m or cnt[newx][newy] != 0) continue;
			if (g[newx][newy] != g[curx][cury] and g[newx][newy] != '.' and g[curx][cury] != '.') continue;
			
			cnt[newx][newy] = id;
			q.push({newx, newy});
		}
	}
	
	return;
}

signed main (){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	dx.push_back(1); dx.push_back(-1); dx.push_back(0); dx.push_back(0);
	dy.push_back(0); dy.push_back(0); dy.push_back(-1); dy.push_back(1);
	
	int t; cin >> t;
	while (t--){
		cin >> n >> m >> q;
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; i++){
			for (int j = 0; j < m; j++){
				cin >> g[i][j];
			}
		}
		
		int idx = 1; 
		for (int i = 0; i < n; i++){
			for (int j = 0; j < m; j++){
				if (cnt[i][j] == 0) {
					bfs(i, j, idx);
					idx++;
				}
			}
		}
		
		while(q--){
			int r1, r2, c1, c2;
			cin >> r1 >> c1 >> r2 >> c2;
			if (cnt[r1][c1] == cnt[r2][c2]) cout << "YES" << '\n';
			else cout << "NO" << '\n';
		}
	}
	
	
	return 0;
}
