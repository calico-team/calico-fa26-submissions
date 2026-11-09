#include <bits/stdc++.h>
using namespace std;

int p[200005];
vector<int> adj[200005];

void dfs(int node, int parent) {
    p[node] = parent;
    for (auto i:adj[node]) {
        if (i != parent) {
            dfs(i,node);
        }
    }
}

int main() {
    string s;
    cin >> s;
    if (s == "FIRST") {
        int n;
        cin >> n;
        for (int i = 0; i < n-1; i++) {
            int a,b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        dfs(1,0);
        for (int i = 2; i <= n; i++) {
            p[1] += p[i];
            p[1] %= n;
        }
        for (int i = 1; i <= n; i++) {
            cout << p[i] << " ";
        }
        cout << "\n";
    }
    else {
        int n;
        cin >> n;
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            cin >> p[i];
        }
        if (p[1] == -1) {
            for (int i = 2; i <= n; i++) {
                cout << i << " " << p[i] << "\n";
            }
            return 0;
        }
        int x;
        for (int i = 2; i <= n; i++) {
            if (p[i] == -1) {
                x = i;
            }
            else {
                sum += p[i];
                sum %= n;
            }
        }
        p[x] = (p[1]-sum+n)%n;
        if (p[x] == 0) {
            p[x] = n;
        }
        for (int i = 2; i <= n; i++) {
            cout << i << " " << p[i] << "\n";
        }
    }
}