#include <bits/stdc++.h>
using namespace std;

const int N = 10005;
int p[N], d[N], cnt[N];

int dfs(int u){
    if(u == 0){
        return 0;
    }
    if(d[u] == 0){
        d[u] = dfs(p[u]) + 1;
    }
    return d[u];
}
int main() {
	int t;
    cin >> t;
    for(int q = 0; q < t; q++){
        int n, m, k;
        cin >> n >> m >> k;
        for(int i = 1; i <= n; i++){
            cin >> p[i];
            d[i] = 0;
            cnt[i] = 0;
        }
        for(int i = 1; i <= n; i++){
            cnt[dfs(i)]++;
        }
        int ans = 0;
        int total = 0;
        for(int i = 1; i <= min(m, n);i++){
            total += cnt[i];
            ans = min(ans + k, total);
        }
        cout << ans << '\n';
    }
}