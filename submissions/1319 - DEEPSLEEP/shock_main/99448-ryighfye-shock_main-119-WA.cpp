#include<bits/stdc++.h>
#define num(x, y) ((x - 1) * (m + 1) + y)
const int N = 2e6 + 5;
using namespace std;
int T, n, m, q;
int x[N], y[N], p[N];
int fa[N], sz[N];
int qrt[N];
vector<int> ans[1005];
int find(int x){
    if(fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}
void merge(int x, int y){
    x = find(x); y = find(y);
    if(x == y) return;
    // if(sz[x] > sz[y]) swap(x, y);
    fa[x] = y;
    sz[y] += sz[x];
}
void recover(int x, int y, int p){
    for(int i = max(1, x - p); i <= min(n, x + p); ++i){
        int dis = p * p - (x - i) * (x - i) + 1;
        if(dis < 0) continue;
        int q = sqrt(dis - 1);
        // cout << " " << i << " " << dis << " " << q << endl;
        for(int j = max(1, y - q); j <= min(m, y + q); j = find(num(i, j + 1)) - (i - 1) * (m + 1)){
            int now = dis - (y - j) * (y - j);
            if(now <= 0) continue;
            ans[i][j] = now;
            // if(j == m) break;
            merge(num(i, j), num(i, j + 1));
            // cout << i << " " << j << " " << find(num(i, j)) - (i - 1) * m << " " << find(num(i, j + 1)) - (i - 1) * m << endl;
        }
    }
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T--){
        bool flag = false;
        cin >> n >> m >> q;
        if(n > m){
            flag = true;
            swap(n, m);
        }
        for(int i = 1; i <= n; ++i){
            ans[i].clear();
        }
        for(int i = 1; i <= n; ++i){
            ans[i].resize(m + 1);
        }
        for(int i = 1; i <= q; ++i){
            cin >> x[i] >> y[i] >> p[i];
            ++x[i]; ++y[i];
            if(flag) swap(x[i], y[i]);
        }
        for(int i = 1; i <= n * m + n; ++i){
            fa[i] = i; sz[i] = 1;
        }
        for(int i = q; i >= 1; --i){
            recover(x[i], y[i], p[i]);
        }
        if(!flag){
            for(int i = 1; i <= n; ++i){
                for(int j = 1; j <= m; ++j){
                    cout << ans[i][j] << " ";
                }
                cout << "\n";
            }
        }else{
            for(int i = 1; i <= m; ++i){
                for(int j = 1; j <= n; ++j){
                    cout << ans[j][i] << " ";
                }
                cout << "\n";
            }
        }
        // cout.flush();
    }
    return 0;
}/*
T8 That Was an Earthquake?
easy
*/