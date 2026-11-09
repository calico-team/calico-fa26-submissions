#include <bits/stdc++.h>
#define ll long long
using namespace std;

struct BIT {
    int sz;
    vector<int> tree;
    BIT(int n) :sz(n), tree(n + 1, 0) {}
    void add(int i, int delta) {
        for (; i <= sz; i += i & -i) tree[i] += delta;
    }
    int query(int i) {
        if (i <0) return 0;
        if (i> sz) i = sz;
        int sum =0;
        for (; i >0; i -= i & -i) sum += tree[i];
        return sum;
    }
    int query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

void solve() {
    int n;
    ll k;
    if (!(cin >> n >> k)) return;

    struct Drone {
        ll x,y,z;
        char d;
    };

    vector<Drone> east, north;
    for (int i =0; i< n; i++) {
        ll x, y, z;
        char d;
        cin >> x >>y >> z >>d;
        if (d == 'E') east.push_back({x, y, z, d});
        else north.push_back({x, y, z, d});
    }

    ll total_water = (ll)n * k;
    ll lost_water = 0;

    map<ll, vector<Drone>> e_groups, n_groups;
    for (auto& dr : east) e_groups[dr.x + dr.y].push_back(dr);
    for (auto& dr : north) n_groups[dr.x + dr.y].push_back(dr);

    BIT bit(100005);

    for (auto& [s, e_list] : e_groups) {
        if (!n_groups.count(s)) continue;
        auto& n_list = n_groups[s];

        struct Event {
            ll x;
            int type; // 0: north insert, 1: R query (+1), 2: L query (-1)
            ll z;
            int id;
        };

        vector<Event> events;
        for (auto& nd : n_list) {
            events.push_back({nd.x, 0, nd.z, 0});
        }

        vector<ll> z_vals(e_list.size());
        vector<ll> greater_net(e_list.size(), 0);
        vector<ll> less_net(e_list.size(), 0);

        for (int i =0; i < (int)e_list.size(); i++) {
            z_vals[i] = e_list[i].z;
            ll R =e_list[i].x + k - 1;
            ll L =e_list[i].x - 1;
            if (R >100005) R = 100005;
            if (L < -1) L = -1;

            events.push_back({R, 1, e_list[i].z, i});
            events.push_back({L, 2, e_list[i].z, i});
        }

        sort(events.begin(), events.end(),[](const Event& a, const Event& b) {
            if (a.x != b.x) return a.x < b.x;
            return a.type < b.type;
        });

        vector<ll> active_z;

        for (auto& ev : events) {
            if (ev.type ==0) {
                bit.add(ev.z + 1, 1);
                active_z.push_back(ev.z + 1);
            } else {
                int z_idx =ev.z + 1;
                // coba ini diperbaikin dikit sm gw biar ga terhitung itunya
                int g_cnt =bit.query(z_idx + 1, 100002);
                int l_cnt = bit.query(1, z_idx - 1);

                if (ev.type ==1) {
                    greater_net[ev.id] += g_cnt;
                    less_net[ev.id] += l_cnt;
                } else {
                    greater_net[ev.id] -= g_cnt;
                    less_net[ev.id] -= l_cnt;
                }
            }
        }

        for (int i = 0; i < (int)e_list.size(); i++) {
            lost_water +=greater_net[i] + less_net[i];
        }

        for (auto z_val : active_z) {
            bit.add(z_val, -1);
        }
    }

    cout << total_water - lost_water << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}