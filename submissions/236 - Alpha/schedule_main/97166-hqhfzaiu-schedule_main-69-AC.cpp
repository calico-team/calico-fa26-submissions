#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--){
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> p(n + 1), h(n + 1, 1);
        vector<vector<int>> c(n + 1);
        for (int i = 1; i <= n; i++){
            cin >> p[i];
            c[p[i]].push_back(i);}
        vector<int> o = {0};
        for (int i = 0; i < (int)o.size(); i++)
            for (int x : c[o[i]]) o.push_back(x);
        for (int i = (int)o.size() - 1; i > 0; i--) h[p[o[i]]] = max(h[p[o[i]]], h[o[i]] + 1);
        priority_queue<pair<int, int>> q;
        for (int x : c[0]) q.push({h[x], x});
        int ans = 0;
        while (m-- && !q.empty()){
            vector<int> v;
            while ((int)v.size() < k && !q.empty()){
                v.push_back(q.top().second);
                q.pop();}
            ans += v.size();
            for (int x : v)
                for (int y : c[x]) q.push({h[y], y});}
        cout << ans << "\n";}}