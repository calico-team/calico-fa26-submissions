#include <bits/stdc++.h>
using namespace std;
vector<long long> adj[200005];
long long par[200005];
bool vis[200005];

void dfs(long long n) {
    vis[n] = true;
    for (long long i : adj[n]) {
        if (vis[i]) continue;
        par[i] = n;
        dfs(i);
    }
}


int main() {
    string s;
    cin >> s;
    if (s == "FIRST") {
        long long n;
        cin >> n;
        for (long long i = 0; i < n-1; i++) {
            long long a, b;
            cin >> a >> b;
            adj[a-1].push_back(b-1);
            adj[b-1].push_back(a-1);
        }
        dfs(0);
        long long sum = 0;
        for (long long i = 1; i < n; i++) {
            cout << par[i] << " ";
            sum += par[i];
            sum %= 1000000;
        }
        cout << sum << " ";
    }
    if (s == "SECOND") {
        int n;
        cin >> n;
        long long a[n];
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] != -1) sum += a[i];
        }
        sum -= a[n-1];
        long long prevsum = a[n-1];
        while (sum <= prevsum) sum += 1000000;
        sum -= 1000000;
        for (long long i = 0; i < n-1; i++) {
            if (a[i] == -1) cout << i+2 << ' ' << prevsum-sum+1 << endl;
            else cout << i+2 << ' ' << a[i]+1 << endl;
        }
    }
}

// 12 13 34 25