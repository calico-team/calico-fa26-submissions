#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define all(x) x.begin(), x.end()

void solve() {
    int N, R; cin >> N >> R; 
    vector<int> A(N); 

    for (int& i : A) cin >> i;

    priority_queue<ll, vector<ll>, greater<ll>> pq;
    pq.push(0); pq.push(0);

    for (ll i : A) {
        ll t = pq.top(); pq.pop();
        if (t <= i) {
            pq.push(max(pq.top(), i) + R);
        }
        else {
            cout << "NO\n";
            return; 
        }
    }

    cout << "YES\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t; cin >> t; 
    while(t--)
        solve();
}