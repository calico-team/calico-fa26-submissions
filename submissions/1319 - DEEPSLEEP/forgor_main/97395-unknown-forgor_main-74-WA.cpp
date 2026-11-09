#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
string TEST;
int n, f[N];
vector<int> e[N];

void dfs(int u){
    for (int v : e[u]){
        if (v == f[u]) continue;
        f[v] = u;
        dfs(v);
    }
    return ;
}

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> TEST;
    if (TEST == "FIRST"){
        cin >> n;
        for (int i = 1; i < n; i++){
            int u, v; cin >> u >> v;
            e[u].push_back(v);
        }
        dfs(1);
        int res = 0;
        for (int i = 2; i <= n; i++){
            res ^= f[i];
            cout << f[i] << " ";
        }
        cout << res << endl;
        return 0;
    }
    else {
        cin >> n;
        for (int i = 1; i < n; i++){
            cin >> f[i + 1];
        }
        cin >> f[1];
        if (f[1] != -1){
            for (int i = 2; i <= n; i++)
                if (f[i] != -1) f[1] ^= f[i];
            for (int i = 2; i <= n; i++)
                if (f[i] == -1) f[i] = f[1];
        }
        for (int i = 2; i <= n; i++){
            cout << f[i] << " " << i << endl;
        }
        return 0;
    }
    return 0;
}