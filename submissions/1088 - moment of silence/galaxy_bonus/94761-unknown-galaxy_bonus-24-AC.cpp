#include <bits/stdc++.h>
using namespace std;

int p[40007];
int fs(int x){
    if (p[x] == x) return x;
    return p[x] = fs(p[x]);
}

void ms(int x, int y){
    p[fs(x)] = fs(y);
}

bool ss(int x, int y){
    return fs(x) == fs(y);
}

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void solve(){
    int n, m, q; cin >> n >> m >> q;
    for (int i = 0; i <= n * m; i++) p[i] = i;
    int grid[n+5][m+5];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            char x; cin >> x;
            if (x == '.') grid[i][j] = 0;
            else if (x == 'B') grid[i][j] = 1;
            else grid[i][j] = 2;
        }
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            for (int k = 0; k < 4; k++){
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
                if (grid[i][j] == 0) ms(i*m+j, ni*m+nj);
                else if (grid[i][j] == grid[ni][nj]) ms(i*m+j, ni*m+nj);
            }
        }
    }

    while (q--){
        int a, b, c, d; cin >> a >> b >> c >> d;
        cout << (ss(a*m+b, c*m+d)?"YES\n":"NO\n");
    }
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}
