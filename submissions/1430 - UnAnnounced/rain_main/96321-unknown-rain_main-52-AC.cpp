// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

template<typename T>
ostream& operator << (ostream& out, vector<T>& a) {
    out << "[";
    for (int i = 0; i < a.size(); i++) {
        if (i) out << ", ";
        out << a[i];
    }
    out << "]";
    return out;

}

void solve() {
    int n, k;
    cin >> n >> k;
    // x+y -> x or y
    map<int, set<int>> vert_buckets, hor_buckets;
    map<int, vector<int>> V;
    for (int i = 0; i < n; i++) {
        int x, y, z;
        char c;
        cin >> x >> y >> z >> c;
        int s = x + y;
        if (c == 'N') {
            vert_buckets[s].insert(x);
        } else {
            hor_buckets[s].insert(y);
        }
    }
    long long ans = 0;
    for (auto& x : vert_buckets) {
        V[x.first] = vector<int>(x.second.begin(), x.second.end());
        ans += 1LL * x.second.size() * k;
    }
    for (auto& x : hor_buckets) {
        int s = x.first;
        for (int y : x.second) {
            int x = s - y;
            ans += k;
            if (V.count(s) == 0) continue;
            vector<int>& enemy = V[s];
            auto st = lower_bound(enemy.begin(), enemy.end(), x);
            auto fi = upper_bound(enemy.begin(), enemy.end(), x + k - 1);
            int delta = fi - st;
            //cout << "enemy x's=" << enemy << endl;
            //cout << "our x = " << x << endl;
            //cout << "delta= " << delta << endl;
            ans -= delta;
        }
    }
    cout << ans << "\n";
}

int main() {
	int t;
    cin >> t;
    while (t--) solve();
}
