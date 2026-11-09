#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
typedef long long ll;
const int MAXN = 4005;
string v[15];
int vis[15][MAXN][2]; 
int qx[80005], qy[80005], qm[80005];
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

void solve()
{
    int n, m, q; cin >> n >> m >> q;
    for(int i = 0; i < n; i++){
        cin >> v[i];
        for(int j = 0; j < m; j++){
            vis[i][j][0] = 0; 
            vis[i][j][1] = 0;
        }
    }
    int cnt = 0;
    while(q--){
        ++cnt;
        int r1, c1, r2, c2, k; cin >> r1 >> c1 >> r2 >> c2 >> k;
        int h = 0, t = 0;
        qx[t] = r1; qy[t] = c1; qm[t] = 0; t++;
        vis[r1][c1][0] = cnt;
        bool flag = false;
        int dd = 0;
        while(h < t){
            if(dd > k) break;
            while(h < t){
                int kk = qm[h];
                if(qx[h] == r2 && qy[h] == c2){
                    flag = true; 
                    break;
                }
                if(v[qx[h]][qy[h]] == '.'){
                    if(vis[qx[h]][qy[h]][1-kk] != cnt){
                        vis[qx[h]][qy[h]][1-kk] = cnt; 
                        qx[t] = qx[h]; qy[t] = qy[h]; qm[t] = 1-kk; t++;
                    }
                }
                for(int d = 0; d < 4; d++){
                    int xx = qx[h] + dx[d];
                    int yy = qy[h] + dy[d];
                    if(xx >= 0 && yy >= 0 && xx < n && yy < m){
                        if((v[xx][yy] == '.') || (v[xx][yy] == 'B' && kk == 0) || (v[xx][yy] == 'R' && kk == 1)){
                            if(vis[xx][yy][kk] != cnt){
                                vis[xx][yy][kk] = cnt;
                                qx[t] = xx; qy[t] = yy; qm[t] = kk; t++;
                            }
                        }
                    }
                }
                h++;
            }
            if(flag) break;
            dd++;
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