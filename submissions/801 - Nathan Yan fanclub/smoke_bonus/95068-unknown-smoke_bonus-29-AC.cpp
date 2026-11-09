#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
#define inf 1000000000000000LL
#define mod 1000000007LL
#define FOR(i,a,b) for(int i = a; i < b; i++)

void solve() {
    ll n, r;
    cin >> n >> r;
    vector <ll> l1(n);
    priority_queue <ll, vector <ll>, greater <ll>> pq;
    for (int i = 0; i < n; i++){
        cin >> l1[i];
    }
    ll last1 = 0;
    for (int i = 0; i < n; i++){
        while (pq.size() >= 1){
            ll cur = pq.top();
            ll v = max(last1, cur);
            if (v + r <= l1[i]){
                last1 = v + r;
                pq.pop();
            }
            else{
                break;
            }
        }
        if (pq.size() < 2){
            pq.push(l1[i]);
        }
        else{
            cout << "NO" << "\n";
            return;
        }
    }
    cout << "YES" << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}