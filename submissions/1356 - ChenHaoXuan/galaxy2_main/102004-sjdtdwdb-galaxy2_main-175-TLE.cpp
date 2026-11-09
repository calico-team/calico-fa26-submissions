#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
typedef long long ll;
const int MAXN = 4005;
char v[15][MAXN];
int a[15][MAXN][2];   
int vis[15][MAXN][2]; 
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

bool check(int n,int m,int i, int j, int k) {
    if (i < 0 || j < 0 || i >= n || j >= m) return false;
    if (v[i][j] == '.') return true;
    if (v[i][j] == 'B' && k == 0) return true; 
    if (v[i][j] == 'R' && k == 1) return true; 
    return false;
}

void solve()
{
    int n, m, q; cin >> n >> m >> q;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> v[i][j];
            vis[i][j][0] = 0; 
            vis[i][j][1] = 0;
        }
    }
    int cnt = 0;
    while(q--){
        ++cnt;
        int r1, c1, r2, c2, k; cin >> r1 >> c1 >> r2 >> c2 >> k;
        queue<pair<pair<int,int>,int>>qq;
        qq.push({{r1, c1}, 0});
        vis[r1][c1][0] = cnt;
        a[r1][c1][0] = 0;
        bool flag = false;
        while(qq.size()){
            auto u = qq.front(); qq.pop();
            int x = u.first.first;
            int y = u.first.second;
            int kk = u.second;
            if(x == r2 && y == c2){
                flag = true; 
                break;
            }
            if(a[x][y][kk] >= k) continue;
            if(v[x][y] == '.'){
                if(vis[x][y][1-kk] != cnt){
                    vis[x][y][1-kk] = cnt; 
                    a[x][y][1-kk] = a[x][y][kk] + 1;
                    qq.push({{x,y}, 1-kk});
                }
            }
            for(int d=0;d<4;d++){
                int xx = x + dx[d];
                int yy = y + dy[d];
                if(check(n, m, xx, yy, kk) && vis[xx][yy][kk] != cnt){
                    vis[xx][yy][kk] = cnt;
                    a[xx][yy][kk] = a[x][y][kk] + 1;
                    qq.push({{xx, yy}, kk});
                }
            }
        }
        if(flag) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t; cin >> t;
    while(t--) solve();
    return 0;
}