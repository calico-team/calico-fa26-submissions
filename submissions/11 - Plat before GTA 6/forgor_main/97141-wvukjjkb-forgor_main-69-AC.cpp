#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
#include <numeric>
#include <queue>
#include <stack>
#include <iomanip>
#include <array>
#include <functional>
#include <bitset>
using namespace std;

void baseIO(string s = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if (s.size()) {
        freopen((s + ".in").c_str(), "r", stdin);
        freopen((s + ".out").c_str(), "w", stdout);
    }
}

int subcount = 376;

#define ll long long
#define db long double
#define all(x) (x).begin(), (x).end()

void solvefirst() {
    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        --a, --b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> p(n);
    function<void(int, int)> dfs = [&](int par, int cur) {
        p[cur] = par;
        for (int nxt : adj[cur]) {
            if (nxt != par) {
                dfs(cur, nxt);
            }
        }
    };
    dfs(-1, 0);

    int x = 0;
    for (int i = 1; i < n; i++) {
        x ^= p[i];
    }

    x += n + 1;

    p[0] = x;

    for (int x : p) {
        cout << x << ' ';
    }
    cout << endl;
}

void solvesecond() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int x = 0;
    for (int v : a) {
        if (v != -1) {
            if (v >= n + 1) v -= (n + 1);
            x ^= v;
        }
    }

    int i = find(all(a), -1) - a.begin();

    if (a[0] == -1) {
        // do nothing
    } else {
        a[i] = x;
    }

    for (int i = 1; i < n; i++) {
        cout << i + 1 << ' ' << a[i] + 1 << endl;
    }
}

signed main() {
    baseIO();

    string s;
    cin >> s;
    if (s == "FIRST") {
        solvefirst();
    } else {
        solvesecond();
    }

    return 0;
}