#include <bits/stdc++.h>
using namespace std;
int  t;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int main(){
	cin >> t;
	while(t --){
		 int n, m, q;
		 cin >> n >> m >> q;
		 int a[250][250];
		 for (int i = 0; i<n; i++){
		 	for (int j = 0; j<m; j++){
		 		char tmp;
		 		cin >> tmp;
		 		if (tmp == '.') a[i][j] = 0;
		 		else if (tmp == 'R') a[i][j] = 1;
		 		else a[i][j] = 2;
			 }
		 }
		 for (int i = 1; i<=q; i++){
		 	bool vis[250][250] = {};
		 	int x, y, s, e;
		 	cin >> x >> y >> s >> e;
		 	queue<pair<int, int>  > q;
		 	q.push(make_pair(x, y));
		 	vis[x][y] = true;
		 	bool flg = false;
		 	while(!q.empty()){
		 		int nx = q.front().first;
		 		int ny = q.front().second;
		 		q.pop();
		 		if (nx == s && ny == e){
		 			flg = true;
		 			break;
				 }
				 else if (a[nx][ny] == 0){
				 	for (int j = 0; j<4; j++){
				 		if (nx + dx[j] >= 0 && ny + dy[j] >= 0 && nx + dx[j] < n && ny + dy[j] < m && !vis[nx + dx[j]][ny + dy[j]]){
				 			vis[nx + dx[j]][ny + dy[j]] = true;
				 			q.push(make_pair(nx + dx[j], ny + dy[j]));
						 }
					 }
				 }
				 else if (a[nx][ny] == 1){
				 	for (int j = 0; j<4; j++){
				 		if (nx + dx[j] >= 0 && ny + dy[j] >= 0 && nx + dx[j] < n && ny + dy[j] < m && !vis[nx + dx[j]][ny + dy[j]] && a[nx + dx[j]][ny + dy[j]] != 2){
				 			vis[nx + dx[j]][ny + dy[j]] = true;
				 			q.push(make_pair(nx + dx[j], ny + dy[j]));
						 }
					 }
				 }
				 else if (a[nx][ny] == 2){
				 	for (int j = 0; j<4; j++){
				 		if (nx + dx[j] >= 0 && ny + dy[j] >= 0 && nx + dx[j] < n && ny + dy[j] < m && !vis[nx + dx[j]][ny + dy[j]] && a[nx + dx[j]][ny + dy[j]] != 1){
				 			vis[nx + dx[j]][ny + dy[j]] = true;
				 			q.push(make_pair(nx + dx[j], ny + dy[j]));
						 }
					 }
				 }
			 }if (flg) cout << "YES" << endl;
			 else cout << "NO" << endl;
		 }
	}
}
