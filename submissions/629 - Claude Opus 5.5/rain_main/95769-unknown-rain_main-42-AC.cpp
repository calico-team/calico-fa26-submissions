using namespace std;
#include <bits/stdc++.h>
 
#define yes cout << "YES" << endl;
#define no cout << "NO" << endl;
 
#define ll long long
#define read(arr) for (auto &x: arr) cin >> x;
#define print_vec(arr) for (auto arr_val: arr) { cout << arr_val << " "; } cout << endl
 
// https://codeforces.com/blog/entry/70327, written 5 years ago
ll mod_pow(ll a, ll b, ll m){
    int ans = 1;
    while(b){
        if (b&1) ans = (ans*a) % m;
        b /= 2;
        a = (a*a) % m;
    }
    return ans;
}

// https://usaco.guide/gold/hashing?lang=cpp
long long rng() {
	static std::mt19937 gen(
	    std::chrono::steady_clock::now().time_since_epoch().count());
	return std::uniform_int_distribution<long long>(0, INT64_MAX)(gen);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<array<int, 4>> vec(n);
        map<int, vector<int>> collisions;

        for (auto &val: vec) {
            int x, y, z;
            cin >> x >> y >> z;
            char c;
            cin >> c;

            val = {x, y, z, c == 'N'};
            if (c == 'E') {
                collisions[x+y].push_back(y);
            }
        }

        for (auto &x: collisions) sort(x.second.begin(), x.second.end());
        auto cnt_in_range = [&](int id, int l, int r) {
            return upper_bound(collisions[id].begin(), collisions[id].end(), r) - lower_bound(collisions[id].begin(), collisions[id].end(), l);
        };
        ll total = (n)* (ll)k;
        for (int i = 0; i < n; i++) {
            if (vec[i][3] == 1) {
                total -= cnt_in_range(vec[i][0] + vec[i][1], vec[i][1], vec[i][1]+k-1);
            }
            //cout << total << "\n";
        }
        cout << total << "\n";

    }
}
