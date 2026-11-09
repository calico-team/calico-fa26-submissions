#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll INF = 1e9 + 10;

ll solve() {

    ll N, R;
    cin >> N >> R;

    vector<ll> A(N);
    for (ll i = 0; i < N; i++) {
        cin >> A[i];
    }

    ll charge = 2;
    queue<ll> nextCharge;

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
            if (nextCharge.empty() && t+R < INF) nextCharge.push(t+R);
            else if (max(t, nextCharge.front()) + R < INF) nextCharge.push(max(t, nextCharge.front())+R);
        } else return false;

    }

    return true;

}

int main() {

    cin.tie(0);
    ios_base::sync_with_stdio(false);

    ll T;
    cin >> T;

    while (T--) {

        if (solve()) {
            cout << "YES" << '\n';
        } else {
            cout << "NO" << '\n';
        }

    }

}