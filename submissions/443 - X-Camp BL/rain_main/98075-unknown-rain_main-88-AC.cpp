#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct drn {
    ll x, y, z;
    char d;
};
void upd(vector<int>& bit, int idx, int val) {
    while (idx < bit.size()) {
        bit[idx] += val;
        idx += idx & (-idx);
    }
}
int qq(const vector<int>& bit, int idx) {
    int s = 0;
    while (idx > 0) {
        s += bit[idx];
        idx -= idx & (-idx);
    }
    return s;
}
void solve() {
    int N; ll K;
    if (!(cin >> N >> K)) return;
    map<ll, vector<drn>> groups;
    for (int i = 0; i < N; ++i) {
        drn dro;
        cin >> dro.x >> dro.y >> dro.z >> dro.d;
        groups[dro.x + dro.y].push_back(dro);
    }
    ll totb = 0;
    vector<int> bit(100005, 0);
    for (auto& pair : groups) {
        auto& mem = pair.second;
        sort(mem.begin(), mem.end(), [](const drn& a, const drn& b) {
            return a.x < b.x;
        });
        vector<drn> ndr;
        vector<drn> edm;
        for (const auto& m : mem) {
            if (m.d == 'E') edm.push_back(m);
            else ndr.push_back(m);
        }
        int r_ptr = 0;
        int l_ptr = 0;
        for (const auto& east : edm) {
            while (r_ptr < ndr.size() && ndr[r_ptr].x <= east.x + K - 1) {
                upd(bit, ndr[r_ptr].z + 1, 1);
                r_ptr++;
            }
            while (l_ptr < ndr.size() && ndr[l_ptr].x < east.x) {
                upd(bit, ndr[l_ptr].z + 1, -1);
                l_ptr++;
            }
            int total_in_bit = r_ptr - l_ptr;
            int hiz = total_in_bit - qq(bit, east.z + 1);
            totb += hiz;
        }
        while (l_ptr < r_ptr) {
            upd(bit, ndr[l_ptr].z + 1, -1);
            l_ptr++;
        }
        l_ptr = 0; r_ptr = 0;
        for (const auto& north : ndr) {
            while (r_ptr < edm.size() && edm[r_ptr].x <= north.x) {
                upd(bit, edm[r_ptr].z + 1, 1);
                r_ptr++;
            }
            while (l_ptr < edm.size() && edm[l_ptr].x < north.x - K + 1) {
                upd(bit, edm[l_ptr].z + 1, -1);
                l_ptr++;
            }
            int total_in_bit = r_ptr - l_ptr;
            int hiz = total_in_bit - qq(bit, north.z + 1);
            totb += hiz;
        }
        while (l_ptr < r_ptr) {
            upd(bit, edm[l_ptr].z + 1, -1);
            l_ptr++;
        }
    }
    ll ans = N * K - totb;
    cout << ans << endl;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    if (cin >> T) {
        while (T--) solve();
    }
}