#include <bits/stdc++.h>
using namespace std;
int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};
int main() {
	int t;
	cin >> t;
	while(t--) {
		int n, m, q;
		cin >> n >> m >> q;
		int a[n][m];
		for(int i=0;i<n;i++) {
			string s;
			cin >> s;
			for(int j=0;j<m;j++)
				a[i][j] = (s[j]=='.'?0:(s[j]=='R'?1:2));
		}
		int val[n][m][2][14][n][2];
		memset(val,-1,sizeof(val));
		stack<tuple<int,int,int>> st;
		st.push({0,m-1,0});
		while(st.size()) {
			auto [l, r, h] = st.top();
			st.pop();
			int x = (l + r) / 2;
			for(int p=0;p<n;p++)
				for(int f=0;f<2;f++) {
					if(a[p][x] == f + 1)
						continue;
					queue<tuple<int,int,int>> q;
					q.push({p, x, f});
					val[p][x][f][h][p][f] = 0;
					while(q.size()) {
						auto [cx, cy, cf] = q.front();
						int dist = val[cx][cy][cf][h][p][f];
						q.pop();
						if(val[cx][cy][cf^1][h][p][f] == -1 && a[cx][cy] == 0) {
							val[cx][cy][cf^1][h][p][f] = dist + 1;
							q.push({cx,cy,cf^1});
						}
						for(int dir=0;dir<4;dir++) {
							int nx = cx + dx[dir], ny = cy + dy[dir];
							if(!(0 <= nx && nx < n))
								continue;
							if(!(l <= ny && ny <= r))
								continue;
							if(a[nx][ny] == cf + 1)
								continue;
							if(val[nx][ny][cf][h][p][f] != -1)
								continue;
							val[nx][ny][cf][h][p][f] = dist + 1;
							q.push({nx,ny,cf});
						}
					}
				}
			if(l != r) {
				st.push({l, x, h+1});
				st.push({x+1, r, h+1});
			}
		}
		while(q--) {
			int rs, cs, re, ce, k;
			cin >> rs >> cs >> re >> ce >> k;
			int l = 0, r = m-1, h = 0;
			bool ok = 0;
			while(1) {
				int x = (l + r) / 2;
				for(int p=0;p<n;p++)
					for(int f=0;f<2;f++) {
						int d1 = val[rs][cs][0][h][p][f];
						int d2 = val[re][ce][0][h][p][f];
						int d3 = val[re][ce][1][h][p][f];
						if(d1 != -1 && d2 != -1 && d1 + d2 <= k)
							ok = 1;
						if(d1 != -1 && d3 != -1 && d1 + d3 <= k)
							ok = 1;
					}

				if((cs <= x) != (ce <= x))
					break;
				if(l == r)
					break;
				if(min(cs, ce) <= x)
					r = x;
				else
					l = x + 1;
				h++;
			}
			cout << (ok?"YES\n":"NO\n");
		}
	}
}
