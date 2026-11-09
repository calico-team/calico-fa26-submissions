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
        int n, m, k;
        cin >> n >> m >> k;

        vector<int> parent(n); read(parent);
        
        vector<vector<int>> children(n);

        for (int i = 0; i < n; i++) {
            if (parent[i] != 0) {
                children[parent[i]-1].push_back(i);
            }
        }
        vector<int> depth_store(n);
        function<int(int, int)> depth;
        depth = [&](int node, int par) {
            int deep = 0;
            for (auto &x: children[node]) {
                deep = max(deep, depth(x, node));
            }
            deep++;
            depth_store[node] = deep;
            return deep;
        };

        priority_queue<array<int, 2>> bfs;
        for (int i = 0; i < n; i++) {
            if (parent[i] == 0) {
                depth(i, -1);
                bfs.push({depth_store[i], i});
            }
        }

        int total = 0;
        for (int i = 0; i < m && bfs.size() > 0; i++) {
            int taken = 0;
            vector<array<int, 2>> add;
            while (taken < k && bfs.size() > 0) {
                auto top = bfs.top(); bfs.pop();
                total++;
                taken++;
                for (auto &x: children[top[1]]) {
                    add.push_back({depth_store[x], x});
                }
            }
            for (auto &x: add) {
                bfs.push(x);
            }
        }
        cout << total << "\n";
        
    }
}
