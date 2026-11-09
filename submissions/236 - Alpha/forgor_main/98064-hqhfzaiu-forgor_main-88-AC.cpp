#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    int n;
    cin >> s >> n;
    if (s == "FIRST"){
        vector<vector<int>> g(n + 1);
        for (int i = 1; i < n; i++){
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);}
        vector<int> p(n + 1, 0), a(n + 1, 0), st = {1};
        while (!st.empty()){
            int u = st.back();
            st.pop_back();
            for (int v : g[u]) if (v != p[u]) {
                p[v] = u;
                st.push_back(v);}}
        for (int i = 2; i <= n; i++){
            a[i] = p[i];
            a[1] ^= p[i];}
        for (int i = 1; i <= n; i++) cout << a[i] << " \n"[i == n];
    } else {
        vector<int> a(n + 1);
        int k = 0;
        for (int i = 1; i <= n; i++){
            cin >> a[i];
            if (a[i] == -1) k = i;}
        if (k > 1){
            int x = a[1];
            for (int i = 2; i <= n; i++) if (i != k) x ^= a[i];
            a[k] = x;}
        for (int i = 2; i <= n; i++) cout << i << " " << a[i] << "\n";}}