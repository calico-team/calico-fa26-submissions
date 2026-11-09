#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 5;
const int LOG = 17, MAXB = 1<<LOG;
const int MOD = 998244353;
const int mod = 1e9 + 7;
const int K = 5e3+5;

vector<int> sum(4 * N);

void update(int cur, int l, int r, int pos) {
    if (l == r) {sum[cur]++;return;}
    int m = (l + r) / 2;
    if (pos <= m) update(2 * cur, l, m, pos);
    else update(2 * cur + 1, m + 1, r, pos);
    sum[cur] = sum[2 * cur] + sum[2 * cur + 1];
}
int query(int cur, int l, int r, int ql, int qr) {
    if (qr < l or r < ql) return 0;
    if (ql <= l && r <= qr)return sum[cur];
    int m = (l + r) / 2;
    return query(2 * cur, l, m, ql, qr) + query(2 * cur + 1, m + 1, r, ql, qr);
}
void solve(){
    int n, k;
    cin >> n >> k;

    map<int, pair<vector<array<int, 3>>, vector<array<int, 3>>>> gr;
    for (int i = 0; i < n; i++) {
        int x, y, z;
        char d;
        cin >> x >> y >> z >> d;
        if (d == 'E')gr[x + y].first.push_back({x, y, z});
        else gr[x + y].second.push_back({x, y, z});
    }
    int ans = 0;
    for (auto& [s, g] : gr) {
        auto E = g.first;
        auto V = g.second;
        {
            vector<int> vals;
            for (auto d : V) vals.push_back(d[2]);

            if (!vals.empty() && !E.empty()) {
                sort(vals.begin(), vals.end());
                vals.erase(unique(vals.begin(), vals.end()), vals.end());

                sort(V.begin(), V.end(), [](auto a, auto b) { return a[0] < b[0]; });

                vector<array<int, 3>> ev;

                for (auto d : E) {
                    ev.push_back({d[0] + k - 1, d[2], 1});
                    ev.push_back({d[0] - 1, d[2], -1});
                }

                sort(ev.begin(), ev.end());

                int sz = vals.size();
                for(int ui = 0 ; ui < 4 * sz+5 ; ui ++)sum[ui]=0;

                int ptr = 0;

                for (auto e : ev) {
                    while (ptr < (int)V.size() && V[ptr][0] <= e[0]) {
                        int pos = lower_bound(
                            vals.begin(), vals.end(), V[ptr][2]
                        ) - vals.begin();

                        update(1, 0, sz - 1, pos);
                        ptr++;
                    }

                    int pos = upper_bound(
                        vals.begin(), vals.end(), e[1]
                    ) - vals.begin();

                    int cnt = 0;
                    if (pos < sz)
                        cnt = query(1, 0, sz - 1, pos, sz - 1);

                    ans += e[2] * cnt;
                }
            }
        }

        {
            vector<int> vals;
            for (auto d : E) vals.push_back(d[2]);

            if (!vals.empty() && !V.empty()) {
                sort(vals.begin(), vals.end());
                vals.erase(unique(vals.begin(), vals.end()), vals.end());

                sort(E.begin(), E.end(),[](auto a, auto b) { return a[0] < b[0]; });

                vector<array<int, 3>> ev;
                for (auto d : V) {
                    ev.push_back({d[0], d[2], 1});
                    ev.push_back({d[0] - k, d[2], -1});
                }
                sort(ev.begin(), ev.end());

                int sz = vals.size();
                for(int ui = 0 ; ui < 4 * sz+5 ; ui ++)sum[ui]=0;
                

                int ptr = 0;

                for (auto e : ev) {
                    while (ptr < (int)E.size() && E[ptr][0] <= e[0]) {
                        int pos = lower_bound(
                            vals.begin(), vals.end(), E[ptr][2]
                        ) - vals.begin();

                        update(1, 0, sz - 1, pos);
                        ptr++;
                    }

                    int pos = upper_bound(
                        vals.begin(), vals.end(), e[1]
                    ) - vals.begin();

                    int cnt = 0;
                    if (pos < sz)
                        cnt = query(1, 0, sz - 1, pos, sz - 1);

                    ans += e[2] * cnt;
                }
            }
        }
    }

    cout << n * k - ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(0); //DO NOT USE THIS IN INTERACTIVE
    cin.tie(0), cout.tie(0);
    cout << fixed<<setprecision(9);
    int t = 1;
    cin >> t;
    while(t --){
        solve();
    }
}
