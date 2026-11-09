#include <bits/stdc++.h>
using namespace std;

#define abysr ios_base::sync_with_stdio(0); cin.tie(0);
#define ll long long
#define vll vector<long long>
#define endl "\n"

int main() {
    abysr

    ll t;
    cin >> t;

    while (t--) {
        ll n, r;
        cin >> n >> r;

        ll charge = 2;
        ll next = 0;
        bool ans = true;

        for (int i = 0; i < n; i++) {
            ll a;
            cin >> a;

            if (charge < 2 && a >= next) {
                charge++;
                next += r;
            }

            if (charge == 0) {
                ans = false;
            }
            else {
                charge--;

                if (charge == 1) {
                    next = a + r;
                }
                else {
                    next += r;
                }
            }
        }

        if (ans){
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }
}