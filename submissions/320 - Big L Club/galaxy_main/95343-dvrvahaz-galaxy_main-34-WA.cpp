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

        for(auto [ai,bj] : dirs) {
            int ni = i+ai, nj = j+bj;
            if(ni>=n||nj>=m||ni<0||nj<0) continue;

            for(int nk = 0; nk < 2; nk++) {
                if(k!=nk) {
                    if(a[i][j]!='.') continue;
                }

                if(a[ni][nj]=='R' && nk==1) continue;
                if(a[ni][nj]=='B' && nk==0) continue;
                
                if(!visited[ni][nj][nk]) {
                    visited[ni][nj][nk] = true;
                    q.push({ni,nj,nk});
                }
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