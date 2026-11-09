#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll t; cin >> t;
    while (t--){
        ll a, b; cin >> a >> b;
        vector <ll> v(a + 1, 0);
        for (int i = 1; i <= a; i++) cin >> v[i];
        ll c1 = 0, c2 = 0; bool found = false;
        for (int i = 1; i <= a; i++){
            if (v[i] >= c1) c1 = v[i] + b;
            else if (v[i] >= c2) c2 = c1 + b;
            else{
                found = true;
                break;
            }
        }
        if (found) cout << "NO" << endl;
        else cout << "YES" << endl;
    }
}