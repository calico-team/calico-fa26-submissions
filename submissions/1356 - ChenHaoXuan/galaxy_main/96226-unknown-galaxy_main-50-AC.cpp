#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
typedef long long ll;
const int MAXN = 1005;
char v[MAXN][MAXN];
int a[MAXN][MAXN][2]; 
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
    int n,m,q; cin>>n>>m>>q;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>v[i][j];
            a[i][j][0] = -1;
            a[i][j][1] = -1;
        }
    }
    queue<pair<pair<int,int>,int>>qq;
    int val = 0;
    for(int i=0;i<n;i++){
        for(int j =0;j<m;j++){
            for(int k=0;k<2;k++){
                if(a[i][j][k] == -1 && check(n,m,i,j,k)){
                    qq.push({{i, j}, k});
                    a[i][j][k] = val;
                    while(qq.size()){
                        auto u = qq.front(); qq.pop();
                        int x = u.first.first;
                        int y =u.first.second;
                        int kk = u.second;
                        if(v[x][y] == '.'){
                            if(a[x][y][1-kk] == -1){
                                a[x][y][1-kk] = val;
                                qq.push({{x,y}, 1-kk});
                            }
                        }
                        for(int d=0;d<4;d++){
                            int xx = x + dx[d];
                            int yy = y + dy[d];
                            if(check(n,m,xx, yy, kk) && a[xx][yy][kk]==-1){
                                a[xx][yy][kk]=val;
                                qq.push({{xx, yy}, kk});
                            }
                        }
                    }
                    ++val;
                }
            }
        }
    }
    while(q--){
        int r1, c1, r2, c2; cin>>r1>>c1>>r2>>c2;
        int s = a[r1][c1][0];
        if(s!=-1&&(s==a[r2][c2][0] || s == a[r2][c2][1]))cout << "Yes" << '\n';
        else cout << "No" << "\n";
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t; cin>>t;
    while(t--) solve();
    return 0;
}