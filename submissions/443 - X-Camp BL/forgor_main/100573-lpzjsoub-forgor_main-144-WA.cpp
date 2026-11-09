#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve() {
    string phase;
    if (!(cin >> phase)) return;
    int n; cin >> n;
    if (phase == "FIRST") {
        vector<int> dgdg(n + 1, 0);
        for (int i = 0; i < n - 1; ++i) {
            int u, v; cin >> u >> v;
            dgdg[u]++; dgdg[v]++;
        }
        for (int i = 1; i <= n; ++i) {
            cout << dgdg[i] << (i == n ? "" : " ");
        }
        cout << endl;
    } else {
        vector<int> a(n + 1);
        int misdx = -1;
        ll sumd = 2LL * n - 2;
        ll curs = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            if (a[i] == -1) {
                misdx = i;
            } else {
                curs += a[i];
            }
        }
        a[misdx] = sumd - curs;
        vector<int> dgdg = a;
        int ptr = 1;
        while (ptr <= n && dgdg[ptr] != 1) {
            ptr++;
        }
        int l = ptr;
        for (int i = 1; i <= n; ++i) {
            if (dgdg[i] > 1) {
                for (int j = 0; j < dgdg[i] - 1; ++j) {
                    cout << l << " " << i << "\n";
                    dgdg[l]--;
                    while (ptr <= n && dgdg[ptr] != 1) {
                        ptr++;
                    }
                    l = ptr;
                }
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (dgdg[i] == 1 && i != l) {
                cout << l << " " << i << endl;
                break;
            }
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}