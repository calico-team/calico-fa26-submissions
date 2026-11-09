#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 1e18;
int N;
vector<vector<int>> T;
vector<int> par;
void d0 (int node ){
    for (int i : T[node]) {
        if (i != par[node]) {
            par[i] = node;
            d0(i);
        }
    }
}
void do1() {
    cin >> N;
    T = vector<vector<int>>(N, vector<int>(0));
    par = vector<int>(N, -1);
    for (int i = 0; i < N-1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        T[u].push_back(v);
        T[v].push_back(u);
    }
    par[0] = -2;
    d0(0);
    par[0] = 0;
    for (int i = 1; i < N; i++) {
        par[0] += par[i];
        par[0] %= N;
    }
    for (int i = 0; i < N; i++) {
        if (i != 0) cout << ' ';
        cout << par[i];
    }
    cout << '\n';
}


void do2() {
    cin >> N;
    par = vector<int>(N);
    for (int i = 0;i  < N; i++) cin >> par[i];
    if (par[0] != -1) {
        int cur = -1;
        for (int i = 1; i < N; i++) {
            if (par[i] == -1) {
                cur = i;
                break;
            }
        }
        int x = par[0];
        for (int i = 1; i < N; i++) {
            if (i != cur) {
                x = x + N - par[i];
                x %= N;
            }
        }
        par[cur] = x;
    }
    for (int i = 1; i < N; i++) {
        cout << par[i] + 1 << ' ' << i + 1 << '\n';
    }
}
signed main(){
    cin.sync_with_stdio(false);
    cin.tie(0);
    string s;
    cin >> s;
    if (s[0] == 'F') {
        do1();
    }
    else {
        do2();
    }
    return 0;
}