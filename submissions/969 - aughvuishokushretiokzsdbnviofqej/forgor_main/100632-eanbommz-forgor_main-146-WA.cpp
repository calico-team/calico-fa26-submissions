#include <bits/stdc++.h>
using namespace std;
vector<int> adj[200005];
int par[200005];
int vis[200005];

void dfs(int n) {
    vis[n] = true;
    for (int i : adj[n]) {
        if (vis[i]) continue;
        par[i] = n;
        dfs(i);
    }
}


int main() {
    string s;
    cin >> s;
    if (s == "FIRST") {
        int n;
        cin >> n;
        for (int i = 0; i < n-1; i++) {
            int a, b;
            cin >> a >> b;
            adj[a-1].push_back(b-1);
            adj[b-1].push_back(a-1);
        }
        dfs(0);
        int sum = 0;
        for (int i = 1; i < n; i++) {
            cout << par[i] << " ";
            sum += par[i];
            sum %= 1000000;
        }
        cout << sum << " ";
    }
    if (s == "SECOND") {
        vector<int> a;
        int ai;
        long long sum;
        while (cin >> ai) {
            a.push_back(ai);
            if (ai != -1) sum += ai;
        }
        int n = a.size();
        sum -= a[n-1];
        long long prevsum = a[n-1];
        while (sum <= prevsum) sum += 1000000;
        sum -= 1000000;
        for (int i = 0; i < n-1; i++) {
            if (a[i] == -1) cout << i+2 << ' ' << prevsum-sum+1 << endl;
            else cout << i+2 << ' ' << a[i]+1 << endl;
        }
    }
}

// 12 13 34 25