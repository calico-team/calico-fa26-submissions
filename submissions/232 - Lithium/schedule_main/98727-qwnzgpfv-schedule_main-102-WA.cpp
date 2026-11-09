#include <bits/stdc++.h>
using namespace std;

int p[10005];
int d[10005];
int a[10005]; // used
int b[1005]; // number of things left

void solve() {
    int n,m,k;
    cin >> n >> m >> k;
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        p[i] = 0;
        d[i] = 0;
        a[i] = 0;
        b[i] = 0;
    }
    if (m > 1000) {
        for (int i = 1; i <= 1000; i++) {
            b[i] += k*(m-1000);
        }
    }
    for (int i = 1; i <= min(m,1000); i++) {
        b[i] += (min(m,1000)-i+1)*k;
    }
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        if (p[i] == 0) {
            d[i] = 1;
        }
    }
    for (int i = 1; i <= 1000; i++) {
        for (int j = 1; j <= n; j++) {
            if (d[j] == 0 && d[p[j]] != 0) {
                d[j] = d[p[j]]+1;
            }
        }
    }
    vector<int> v;
    for (int i = 1; i <= n; i++) {
        v.push_back(i);
    }
    sort(v.begin(),v.end(),[](int a, int b) {return d[a] > d[b];});
    for (int i = 0; i < n; i++) {
        int node = v[i];
        if (b[d[node]] == 0) {
            continue;
        }
        int x = d[node];
        while (node != 0) {
            if (a[node]) {
                break;
            }
            ans ++;
            b[d[node]] -= (x-d[node]+1);
            a[node] = 1;
            node = p[node];
        }
    }
    cout << ans << "\n";
}


int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}