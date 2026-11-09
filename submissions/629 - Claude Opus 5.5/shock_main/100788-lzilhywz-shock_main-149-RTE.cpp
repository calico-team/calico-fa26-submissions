using namespace std;
#include <bits/stdc++.h>
 
#define yes cout << "YES" << endl;
#define no cout << "NO" << endl;
 
#define ll long long
#define read(arr) for (auto &x: arr) cin >> x;
#define print_vec(arr) for (auto arr_val: arr) { cout << arr_val << " "; } cout << endl
 
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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

ll dist(array<ll, 5> arr) {
    return arr[4] * arr[4] - (arr[3] - arr[1]) * (arr[3] - arr[1]) - (arr[2] - arr[0]) * (arr[2] - arr[0])+1;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;

    while (t--) {
        int n, m, q;
        cin >> n >> m >> q;

        vector<vector<ll>> vec(n, vector<ll>(m, 0));
        vector<set<int>> used_col(n);
        vector<set<int>> used_row(m);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                used_col[i].insert(j);
                used_row[j].insert(i);
            }
        }

        vector<array<ll, 3>> earthquakes(q);
        for (auto &x: earthquakes) read(x);

        reverse(earthquakes.begin(), earthquakes.end());
        
        for (auto &eq: earthquakes) {
            
            queue<array<ll, 5>> bfs;
            bfs.push({eq[0], eq[1], eq[0], eq[1], eq[2]});
            while(bfs.size() > 0) {
                auto top = bfs.front(); bfs.pop();
                //cerr << top[0] << " " << top[1] << "\n";
                if (dist(top) <= 0) continue;
                if (vec[top[0]][top[1]] == 0) {
                    vec[top[0]][top[1]] = dist(top);
                    used_col[top[0]].erase(top[1]);
                    used_row[top[1]].erase(top[0]);
                }
                if (used_col[top[0]].size() != 0) {
                    auto down = used_col[top[0]].lower_bound(top[1]);
                    auto up = used_col[top[0]].lower_bound(top[1]);
                    if (down != used_col[top[0]].end()) {
                       // cerr << 'a' << "\n";
                        bfs.push({top[0], *down, top[2], top[3], top[4]});
                    }
                    if (up != used_col[top[0]].begin()) {
                       // cerr << 'b' << "\n";
                        up--;
                        bfs.push({top[0], *up, top[2], top[3], top[4]});
                    }
                }
                if (used_row[top[1]].size() != 0) {
                    auto down = used_row[top[1]].lower_bound(top[0]);
                    auto up = used_row[top[1]].lower_bound(top[0]);
                    if (down != used_row[top[1]].end()) {
                        //cerr << 'c' << "\n";
                        bfs.push({*down, top[1], top[2], top[3], top[4]});
                    }
                    if (up != used_row[top[1]].begin()) {
                       // cerr << 'd' << "\n";
                        up--;
                        bfs.push({*up, top[1], top[2], top[3], top[4]});
                    }
                }
            }

        }

        for (auto &x: vec) {
            print_vec(x);
        }
        
    }
}
