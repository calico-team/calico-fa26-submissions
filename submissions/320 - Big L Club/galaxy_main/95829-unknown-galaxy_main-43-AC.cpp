#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<pair<int,int>> dirs = {{0,1},{1,0},{-1,0},{0,-1}};

void solve() {
    int n,m,qn; cin >> n >> m >> qn;
    vector<vector<char>> a(n,vector<char>(m));
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
        char c; cin >> c;
        a[i][j] = c;
    }

    vector<vector<vector<bool>>> visited(n+1,vector<vector<bool>>(m+1,vector<bool>(2,false)));
    visited[n-1][m-1][0] = visited[n-1][m-1][1] = true;
    queue<vector<int>> q;
    q.push({n-1,m-1,1});
    q.push({n-1,m-1,0});

    while(!q.empty()) {
        int i = q.front()[0], j = q.front()[1], k = q.front()[2]; q.pop();
        
        if(a[i][j]=='.') {
            int nk = !k;
            if(!visited[i][j][nk]) {
                visited[i][j][nk] = true;
                q.push({i,j,nk});
            }
        }
        for(auto [ai,bj] : dirs) {
            int ni = i+ai, nj = j+bj;
            if(ni>=n||nj>=m||ni<0||nj<0) continue;

            if(a[i][j]=='R' && k==1) continue;
            if(a[i][j]=='B' && k==0) continue;
            
            if(!visited[ni][nj][k]) {
                visited[ni][nj][k] = true;
                q.push({ni,nj,k});
            }
        }
    }


    while(qn--) {
        int startI,startJ,endI,endJ; cin >> startI >> startJ >> endI >> endJ;
        if(visited[startI][startJ][1]) {
            cout << "YES" << endl;
        }
        else cout << "NO" << endl;
    }
    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--) {
        solve();
    }
}