#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<pair<int,int>> dirs = {{0,1},{1,0},{-1,0},{0,-1}};
vector<vector<char>> a;
vector<vector<int>> cc;

int curr = 0;

int n,m;

void dfs(int i, int j) {
    for(auto [ai,bj] : dirs) {
        int ni = i+ai, nj = j+bj;
        if(ni<0||nj<0||ni>=n||nj>=m) continue;
        if(cc[ni][nj]!=-1) continue;

        if(a[i][j]=='R' && a[ni][nj]=='B') continue;
        if(a[i][j]=='B' && a[ni][nj]=='R') continue;

        cc[ni][nj] = curr;
        dfs(ni,nj);
    }
}

void solve() {
    int qn; cin >> n >> m >> qn;

    a.assign(n+1,vector<char>(m+1,'.'));
    for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) {
        char c; cin >> c;
        a[i][j] = c;
    }

    curr = 0;
    cc.assign(n+1,vector<int>(m+1,-1));

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(cc[i][j]!=-1) continue;

            curr++;
            dfs(i,j);
        }
    }

    while(qn--) {
        int startI,startJ,endI,endJ; cin >> startI >> startJ >> endI >> endJ;
        if(cc[startI][startJ]==cc[endI][endJ]) {
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