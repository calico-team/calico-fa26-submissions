// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;


bool swapped;

const int OMAX = 1000 * 1000 + 10;

long long sqrs[OMAX];

int sqrt_down(long long x) {
    auto it = upper_bound(sqrs, sqrs + OMAX, x);
    return it - sqrs - 1;
}

struct Shock {
    int c;
    int id;
    long long p_rem;
    int center;
};

bool operator <(const Shock& a, const Shock& b) {
    if (a.c != b.c) return a.c < b.c;
    return a.id < b.id;
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    swapped = (n > m);
    if (swapped) swap(n, m);
    vector<vector<Shock> > shocks(n);
    for (int id = 0; id < q; id++) {
        int r, c, p;
        cin >> r >> c >> p;
        if (swapped) swap(r, c);
        for (int i = max(r - p, 0); i <= min(r + p, n - 1); i++) {
            long long new_p = (1LL * p) * p - (1LL * i - r) * (i - r);
            int dc = sqrt_down(new_p);
            shocks[i].push_back({c - dc, id, new_p, c});
            shocks[i].push_back({c + dc + 1, id, new_p, c});
            //cout << "For r=" << i << ": shock is from " << (c - dc) << " to " << (c + dc) << endl;
        }
    }
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        vector<Shock>& s = shocks[i];
        sort(s.begin(), s.end());
        int q = 0;
        map<int, int> active;
        for (int j = 0; j < m; j++) {
            while (q < s.size() && s[q].c <= j) {
                if (active.count(s[q].id) > 0) {
                    active.erase(s[q].id);
                } else {
                    active[s[q].id] = q;
                }
                q++;
            }
            if (!active.empty()) {
                Shock& best = s[active.rbegin()->second];
                ans[i][j] = best.p_rem - (best.center - j) * (best.center - j) + 1;
            } else {
                ans[i][j] = 0;
            }
            //if (i == 0) cout << ans[i][j] << " - " << active.size() << "H" << endl;
        }
    }

    if (swapped) swap(n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; j++) {
            if (j) cout << " ";
            cout << (swapped ? ans[j][i] : ans[i][j]);
        }
        cout << "\n";
    }
}

int main() {
    for (int i = 0; i < OMAX; i++) sqrs[i] = (1LL * i) * i;
	
    int t;
    cin >> t;
    while (t--) solve();
}
