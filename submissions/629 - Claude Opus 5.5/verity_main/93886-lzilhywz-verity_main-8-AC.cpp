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
    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<char> s(k); read(s);
        vector<char> ans(n);
        bool found = false;
        for (auto &x: s) {
            for (int i = 0; i < n; i++) cout << x;
            cout << endl;
            string response;
            cin >> response;
            if (response == "CORRECT") {
                found = true;
                break;
            }
            for (int i = 0; i < n; i++) {
                if (response[i] != '_') {
                    ans[i] = response[i];
                }
            }
        }
        if (!found) {
            for (auto &x: ans) cout << x;
            cout << "\n";
            string p;
            cin >> p;
        }
    }
}
