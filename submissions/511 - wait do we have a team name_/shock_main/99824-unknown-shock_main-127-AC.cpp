#include <bits/stdc++.h>
#define int long long

using namespace std;

struct earthquake{
	int x, y, p;
};

int n, m, q;
vector < vector<int> > nxt;

int find(int x, int y){
	int cur = y;
	while(nxt[x][cur] != cur){
		cur = nxt[x][cur];
	}
	
	while (nxt[x][y] != y){
		int temp = nxt[x][y];
		nxt[x][y] = cur;
		y = temp;
	}
	
	return cur;
}

signed main (){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int t; cin >> t;
	while (t--){
		cin >> n >> m >> q; //n x m, q earthquakes
		vector <earthquake> eq(q);		
		for (int i = 0; i < q; i++){
			cin >> eq[i].x >> eq[i].y >> eq[i].p;
		}
		nxt.assign(n, vector<int> (m+1));
		for (int i = 0; i < n; i++){
			for (int j = 0; j <= m; j++){
				nxt[i][j] = j;
			}
		}
		
		vector < vector<int> > ans(n, vector<int> (m, 0));
		for (int i = q-1; i >= 0; i--){
			int x = eq[i].x; int y = eq[i].y; int p = eq[i].p; int p2 = p*p;
			for (int row = x-p; row <= x+p; row++){
				int dx = row-x;
				int dy = floor(sqrtl(p2-dx*dx));
				int left = y-dy; int right = y+dy;
				
				int nxty = find(row, left);
				while(nxty <= right){
					long long newdy = nxty-y;
					ans[row][nxty] = p2 - dx*dx - newdy*newdy + 1;
					int nxty1 = find(row, nxty+1);
					nxt[row][nxty] = nxty1;
					nxty = nxty1;
				}
			}
		}
		
		for (int i = 0; i < n; i++){
			for (int j = 0; j < m; j++){
				cout << ans[i][j] << " ";
			}
			cout << endl;
		}
	}
	
	return 0;
}


