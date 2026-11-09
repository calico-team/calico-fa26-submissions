#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        ll n;
        ld r;
        cin >> n >> r;
        vector<ll> a(n);
        bool poss = true;
        ll c = 2;
        ll av = -1;
        for (auto &x : a) {
            cin >> x;
        }
        for (int i = 0; i < n && poss; i++){
            ll cd = a[i];
            while (av != -1 && av <= cd) {
                c++;
                if (c < 2) {
                    av += r;
                }
                else {
                    av = -1;
                }
            }
            if (c == 0) {
                poss = false;
                break;
            }
            c--;
            if (av == -1) {
                av = cd + r;
            }
        }
        cout << (poss ? "YES" : "NO") << '\n';

    }

    return 0;
}