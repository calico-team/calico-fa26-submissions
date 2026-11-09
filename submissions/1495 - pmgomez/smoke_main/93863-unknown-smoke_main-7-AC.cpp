#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll solve() {

    ll N, R;
    cin >> N >> R;

    vector<ll> A(N);
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
    }

    ll charge = 2;
    queue<ll> nextCharge;

    // ll ptr = 0;
    for (ll t: A) {

        while (!nextCharge.empty()) {
            ll v = nextCharge.front();
            if (v <= t) {
                charge++;
                nextCharge.pop();
            } else break;
        }

        if (charge > 0) {
            charge--;
            if (nextCharge.empty()) nextCharge.push(t+R);
            else nextCharge.push(max(t, nextCharge.front())+R);
        } else return false;

        // ptr++;

    }

    return true;

}

int main() {

    ll T;
    cin >> T;

    while (T--) {

        if (solve()) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }

    }

}