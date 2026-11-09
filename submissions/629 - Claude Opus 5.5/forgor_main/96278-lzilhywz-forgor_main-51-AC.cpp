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

void first() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n); 
    vector<int> parent(n);
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    function<void(int, int)> dfs;
    dfs = [&](int node, int par) {
        parent[node] = par;
        for (auto &x: adj[node]) {
            if (x == par) continue;
            dfs(x, node);
        }
    };
    dfs(0, 0);
    for (int i = 1; i < n; i++) {
        parent[0] ^= parent[i];
    }
    
    print_vec(parent);
}
void second() {
    int n;
    cin >> n;

    vector<int> vec(n); read(vec);
    int val = 0;
    for (auto &x: vec) {
        if (x > -1) {
            val ^= x;
        }
    }
    for (auto &x: vec) {
        if (x == -1) {
            x = val;
        }
    }
    for (int i = 1; i < n; i++) {
        cout << i+1 << " " << vec[i]+1 << "\n";
    }

}
int main() {
    string s;
    cin >> s;
    if (s == "FIRST") first();
    else second();
}
