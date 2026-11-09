#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(vector<ll>& v, ll r){
    bool good = true;
    pair<ll,ll> charged_times = {1,1};
    for (int i = 0; i < v.size() && good; i++){
        if (charged_times.first <= v[i]){
            charged_times.first = max(v[i],charged_times.second) + r;
        }
        else if (charged_times.second <= v[i]){
            charged_times.second = max(v[i],charged_times.first) + r;
        }
        else{
            good = false;
        }
    }
    if (good){
        cout << "YES\n";
    }else{
        cout << "NO\n";
    }
}

int main() {
	int T;
    cin >> T;
    for (int i = 0; i < T; i++){
        ll n, r;
        cin >> n >> r;
        vector<ll> v(n);
        for (ll &j : v) cin >> j;
        solve(v, r);
    }
}
