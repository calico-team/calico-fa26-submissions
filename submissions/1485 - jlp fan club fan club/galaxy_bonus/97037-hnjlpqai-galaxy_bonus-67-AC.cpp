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

#define M (int)200
#define N (int)1e5
#define INF (int)1e9
#define INFL (int)1e18
#define MOD (int)(1e9+7)
#define fir first
#define sec second

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

struct dat {
	int a, b, c, d;
};

struct qdat {
	int x, y, c;
};

dat S[N+5];
int A[M+5][M+5], vt[M+5][M+5][3];
int t, n, m, q, g;
queue <qdat> que;

void push(int x, int y, int c){
	if(vt[x][y][c] || (A[x][y] == (c^1)) || x < 1 || y < 1 || x > n || y > m) return;
	que.push({x, y, c});
	vt[x][y][c] = g;	
}

void bfs(int x, int y, int c){
	push(x, y, c);
	while(!que.empty()){
		qdat to = que.front();
		que.pop();

		for(int i=0; i<4; i++){
			push(to.x + dx[i], to.y + dy[i], to.c);
		}

		if(A[to.x][to.y] == 2) push(to.x, to.y, to.c^1);
	}
}

signed main(){
	cin.tie(0)->sync_with_stdio(0);
	cin >> t;
	while(t--){
		cin >> n >> m >> q;
		for(int i=1; i<=n; i++){
			string s;
			cin >> s;
			for(int j=0; j<s.size(); j++){
				int a;
				if(s[j] == '.') a = 2;
				else if(s[j] == 'R') a = 0;
				else a = 1;
				A[i][j+1] = a;
			}
		}

		for(int i=1; i<=q; i++){
			cin >> S[i].a >> S[i].b >> S[i].c >> S[i].d;
			S[i].a++;
			S[i].b++;
			S[i].c++;
			S[i].d++;
		}

		for(int i=1; i<=n; i++){
			for(int j=1; j<=m; j++){
				for(int c=0; c<=1; c++){
					vt[i][j][c] = 0;
				}
			}
		}

		g = 0;
		for(int i=1; i<=n; i++){
			for(int j=1; j<=m; j++){
				for(int c=0; c<=1; c++){
					if(vt[i][j][c]) continue;
					g++;
					bfs(i, j, c);
				}
			}
		}

		for(int i=1; i<=q; i++){
			if(vt[S[i].a][S[i].b][0] == vt[S[i].c][S[i].d][0] || vt[S[i].a][S[i].b][0] == vt[S[i].c][S[i].d][1]) cout << "YES\n";
			else cout << "NO\n";
		}
	}
	return 0;
}