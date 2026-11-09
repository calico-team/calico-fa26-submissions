#include<bits/stdc++.h>
using namespace std;

const int N = 20, M = 4000, Q = 1e5, LOG2M = 12;

char grid[N][M];
int dists[N][N][M][1+LOG2M];

// Checks if two adjacent squares are connected
inline bool valid(int x, int y){
	return grid[x>>1][y] == '.' || ((x&1) ? grid[x>>1][y] == 'R' : grid[x>>1][y] == 'B');
}

void calc_sparse_table(int n, int m){
	for (int K = 0; K <= LOG2M; K ++)
		for (int y = 0; y < m; y ++)
			for (int i = 0; i < 2*n; i ++)
				for (int j = 0; j < 2*n; j ++)
					dists[i][j][y][K] = 1e9;
	for (int y = 0; y < m; y ++){
		for (int x = 0; x < 2*n; x ++){
			if (!valid(x, y)) continue;
			dists[x][x][y][0] = 0;
			if (valid(x^1, y)){
				dists[x][x^1][y][0] = 1;
			}
			if (x+2 < 2*n && valid(x+2, y)){
				dists[x][x+2][y][0] = 1;
			}
			if (x-2 >= 0 && valid(x-2, y)){
				dists[x][x-2][y][0] = 1;
			}
		}
		for (int k = 0; k < 2*n; k ++)
			for (int i = 0; i < 2*n; i ++)
				for (int j = 0; j < 2*n; j ++)
					if (valid(i, y) && valid(j, y))
						dists[i][j][y][0] = min(dists[i][j][y][0], dists[i][k][y][0] + dists[k][j][y][0]);
	}
	for (int y1 = 0; y1 < m; y1 ++)
		for (int k = 0; k < 2*n; k ++)
			for (int i = 0; i < 2*n; i ++)
				for (int j = 0; j < 2*n; j ++){
					int y2 = y1+1;
					if (y2 < m && valid(i, y1) && valid(j, y2))
						dists[i][j][y1][1] = min(dists[i][j][y1][1], dists[i][k][y1][0]+dists[k][j][y2][0]+1);
				}
	for (int K = 2; K <= LOG2M; K ++){
		for (int y1 = 0; y1 < m; y1 ++)
			for (int k = 0; k < 2*n; k ++)
				for (int i = 0; i < 2*n; i ++)
					for (int j = 0; j < 2*n; j ++){
						int y3 = y1+(1<<(K-1));
						int y2 = y1+(1<<(K-2));
						if (y3 < m && valid(i, y1) && valid(j, y3))
							dists[i][j][y1][K] = min(dists[i][j][y1][K], dists[i][k][y1][K-1]+dists[k][j][y2][K-1]);
					}
	}
}

void solve(){
	int n, m, q;
	scanf("%d%d%d", &n, &m, &q);
	for (int x = 0; x < n; x ++){
		scanf("%s", grid[x]);
	}
	calc_sparse_table(n, m);
	for (int iter = 0; iter < q; iter ++){
		int query[5];
		scanf("%d%d%d%d%d", &query[0], &query[1], &query[2], &query[3], &query[4]);
		int f = 0;
		if (query[1] > query[3]){
			f = 1;
			swap(query[0], query[2]);
			swap(query[1], query[3]);
		}
		query[0] <<= 1;
		query[2] <<= 1;
		int best[2*n];
		// cout << query[0] << " " << query[1] << endl;
		// cout << valid(0, 2) << endl;
		for (int x = 0; x < 2*n; x ++){
			best[x] = dists[query[0]][x][query[1]][0];
			if (f){
				best[x] = dists[query[0]+1][x][query[1]][0];
			}
			// cout << dists[query[0]][x][query[1]][0] << " ";
		}
		// cout << endl;
		int diff = query[3]-query[1];
		int y1 = query[1];
		for (int k = LOG2M; k > 0; k --){
			if (diff & (1<<(k-1))){
				int y2 = y1+(1<<(k-1));
				int nex[2*n];
				for (int i = 0; i < 2*n; i ++){
					nex[i] = 1e9;
				}
				// cout << k << endl;
				for (int x1 = 0; x1 < 2*n; x1 ++)
					for (int x2 = 0; x2 < 2*n; x2 ++){
						if (valid(x1, y1) && valid(x2, y2)){
							nex[x2] = min(nex[x2], best[x1]+dists[x1][x2][y1][k]);
							// cout << best[x1] << ":" << dists[x1][x2][y1][k] << " ";
						}
					}
				// cout << endl;
				y1 += (1<<(k-1));
				memcpy(best, nex, sizeof(best));
				// for (int x1 = 0; x1 < 2*n; x1 ++){
				// 	cout << best[x1] << " ";
				// }
				// cout << endl;
			}
		}
		int ans = best[query[2]];
		if (!f){
			ans = min(ans, best[query[2]+1]);
		}
		// cout << ans << endl;
		printf(query[4] >= ans ? "YES\n" : "NO\n");
	}
}

int main(){
	int n;
	scanf("%d", &n);
	for (int x = 0; x < n; x ++){
		solve();
	}
}
