// Nov 09 2026, 09:09

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fastIO cin.tie(NULL); ios::sync_with_stdio(NULL)
#define fi first
#define se second

string solve(vector<ll> requests, ll k) {
    ll nextRecharge = -1;
    ll charges = 2;
    for(auto i : requests) {
        if(charges != 2) {
            while(nextRecharge <= i and charges < 2) {
                charges++;
                nextRecharge += k;
                // cerr << "recharge to " << charges << ' ' << nextRecharge << endl;
            }

            if(charges == 2) nextRecharge = -1;
        }

        if(charges == 0) return "NO";

        if(charges == 2) {
            nextRecharge = i + k;
        }
        charges--;
    }

    return "YES";
}

int main() {
    fastIO;

    int T; cin >> T;
    while(T--) {
        ll n, k; cin >> n >> k;
        vector<ll> requests(n); for(auto &i : requests) cin >> i;

        cout << solve(requests, k) << '\n';
    }

    return 0;
}