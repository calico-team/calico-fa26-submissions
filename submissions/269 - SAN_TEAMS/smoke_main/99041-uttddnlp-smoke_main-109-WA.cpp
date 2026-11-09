#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll a[100001];

void sol() {
    ll n,r; cin>>n>>r;
    for(int i=1; i<=n; i++) cin>>a[i];
    // fill(n,r);
    // for(ll i=a[1]; i<=a[n]; i++) cout << smokes[i] << " ";
    // cout << "\n";
    for(int i=1; i<=n-1; i++) {
        if(a[i+1]-a[i] < r) {
            cout << "NO\n"; return;
        }
        if(i%2==0) {
            ll k = (a[i] - a[0])/r;
            if(a[i] >= a[0] + k*r && a[i] <= a[0] + (k+1)*r) continue;
            cout << "NO\n"; return;
        }
        else {
            ll k = (a[i] - a[1])/r;
            if(a[i] >= a[1] + k*r && a[i] <= a[1] + (k+1)*r) continue;
            cout << "NO\n"; return;
        }
    }
    cout << "YES\n";
    // clear(n,r);
}
int main() {
	int t; cin>>t;
    while(t--) sol();
}
