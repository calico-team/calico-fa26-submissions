#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll t; cin >> t;
    while (t--){
        ll a, b; cin >> a >> b;
        vector <ll> v(a + 1, 0);
        for (int i = 1; i <= a; i++) cin >> v[i];
        ll counter = 2; bool found = false;
        for (int i = 1; i <= a; i++){
            if (counter == 0){
                found = true;
                break;
            }
            if (v[i] - v[i - 1] < b) counter--;
            else counter = 2;
        }
        if (found) cout << "NO" << endl;
        else cout << "YES" << endl;
    }
}