#include <bits/stdc++.h>
using namespace std;

int n, m, q;
char s[202][202];
int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1};

int p[40004];

int Find(int x){
	return x == p[x] ? x : p[x] = Find(p[x]);
}

void Union(int x, int y){
	x = Find(x);
	y = Find(y);
	if(x == y) return;
	p[y] = x;
}

int enc(int x, int y){
	return x*m+y;
}

void solve(){
	scanf("%d %d %d", &n, &m, &q);
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			scanf(" %c", &s[i][j]);
		}
	}
	for(int i=0; i<n*m; i++){
		p[i] = i;
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			for(int k=0; k<4; k++){
				int ni = i+dr[k];
				int nj = j+dc[k];
				if(ni < 0 || n <= ni || nj < 0 || m <= nj) continue;
				if(s[i][j] == 'R' && s[ni][nj] == 'B') continue;
				if(s[i][j] == 'B' && s[ni][nj] == 'R') continue;
				Union(enc(i, j), enc(ni, nj));
			}
		}
	}
	while(q--){
		int r1, c1, r2, c2;
		scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
		printf(Find(enc(r1, c1)) == Find(enc(r2, c2)) ? "YES\n" : "NO\n");
	}
}

int main(){
	int t = 1;
	scanf("%d", &t);
	while(t--) solve();
}