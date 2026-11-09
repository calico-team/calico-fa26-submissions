#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;

#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

// Goes to stderr NOT stdout and only active with -DLOCAL. Ex: dbg(x) prints "x = value  ".
#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << "  "
#define dbgln(x) cerr << #x << " = " << (x) << '\n'
#else
#define dbg(x)
#define dbgln(x)
#endif

// To read file, call setIO("filename")
void setIO(const string& name = "") {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!name.empty()) {
        (void)!freopen((name + ".in").c_str(), "r", stdin);
        (void)!freopen((name + ".out").c_str(), "w", stdout);
    }
}

void solve() {
    string s;
    cin>>s;
    int n;
    cin>>n;
    if (s == "FIRST") {
        vector<vector<int>> adj(n);
        for (int i = 0; i < n-1; i++) {
            int a, b;
            cin>>a>>b;
            a--; b--;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        vector<int> parent(n);
        parent[0] = -1;
        queue<int> process;
        process.push(0);
        while (process.size() > 0) {
            int cur = process.front();
            process.pop();
            for (int cand : adj[cur]) {
                if (cand != parent[cur]) {
                    parent[cand] = cur;
                    process.push(cand);
                }
            }
        }
        int total = 0;
        for (int p : parent) {
            if (p == -1) continue; // skipped because parent of 0 is nonexistent
            cout << p << " ";
            total += p;
            total %= n;
        }
        cout << total << "\n";
    } else {
        vector<int> parent(n);
        int missing = -1;
        for (int i = 0; i < n; i++) {
            cin>>parent[i];
            if (parent[i] == -1) missing = i;
        }
        if (parent[n-1] != -1) {
            int total = 0;
            for (int i = 0; i < n-1; i++) {
                if (i != missing) {
                    total += parent[i];
                    total %= n;
                }
            }
            int val = parent[n-1] - total;
            if (val < 0) val += n;
            /* dbgln(total);
            dbgln(val);
            dbgln(missing); */
            parent[missing] = val;
        }
        for (int i = 0; i < n-1; i++) {
            cout << (i+2) << " " << (parent[i]+1) << "\n";
        }
    }
}

int main() {
    setIO();
    solve();
}