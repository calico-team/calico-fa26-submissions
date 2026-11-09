#include <bits/stdc++.h> 
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace std; 
   
using str = string; 
using ll = long long; 
using ld = long double; 
   
#define int long long 
#define show(x) cerr << (#x) << " = " << (x) << '\n'; 
#define output_vector(v) for(auto &x : v){cout << x << " ";}cout << '\n'; 
#define output_pairvector(v) for(auto &x : v){cout << x.first << " " << x.second << '\n';} 
#define vt vector 
#define pii pair<int,int> 
#define piii pair<pair<int,int>, pair<int,int>> 
#define discretize(x) sort(x.begin(), x.end()); x.erase(unique(x.begin(), x.end()), x.end()); 
#define all(x) x.begin(), x.end() 
#define rall(x) x.rbegin(), x.rend() 
#define sz(x) ll(x.size()) 
#define fir first 
#define sec second 

string read_string() {
    string s; cin >> s;
    return s;
}

void print_guess(string guess) {
    cout << guess << endl;
}

void solve(int n, int k, vector<char>& a) {
    vector<int> ptr(n), ans(n, -1);
    str res = "";
    for(int i=0; i<n; ++i) res += "_";
    while(res != "CORRECT") {
		for(int i=0; i<n; ++i) {
			if(res[i] != '_') {
				ans[i] = ptr[i];
			} else {
				ptr[i] = (ptr[i] + 1) % k;
			}
		}
		str guess = "";
		for(int i=0; i<n; ++i) {
			guess += a[ptr[i]];
		}
		print_guess(guess);
		res = read_string();
	}
}

signed main() {
    int T;
    cin >> T;
    
    for (int i = 0; i < T; i++) {
        int N, K;
        cin >> N >> K;

        vector<char> A(K);
        for (int j = 0; j < K; j++) {
            cin >> A[j];
        }

        solve(N, K, A);
    }

    return 0;
}

