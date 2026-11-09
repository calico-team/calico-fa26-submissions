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
    }
    for (int i = 0; i <= 1000; i++) {
        b[i] = 0;
    }
    for (int i = 1; i <= min(m,1000); i++) {
        b[i] += (m-i+1)*k;
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
                assert(d[j] <= 1000);
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
        int x = 0;
        
        while (node != 0) {
            if (a[node] == 0) {
                ans ++;
                x++;
            }
            b[d[node]] -= x;
            assert(b[d[node]] >= 0);
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