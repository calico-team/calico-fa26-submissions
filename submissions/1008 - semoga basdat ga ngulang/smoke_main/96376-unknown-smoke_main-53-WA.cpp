#include <bits/stdc++.h>
using namespace std;

#define abysr ios_base::sync_with_stdio(0); cin.tie(0);
#define ll long long
#define vll vector<long long>
#define endl "\n"


int main() {

	abysr

    ll t = 1;
    cin >> t;
    while (t--){
        ll n,r;
        cin >> n >> r;
        
        vector<ll> vec(n);

        ll now = 0;
        ll charge = 2;
        bool ans = true;
        
        for (int i = 0; i < n; i++){
            cin >> vec[i];
            if (vec[i] - now < r){
                if (charge == 0){
                    ans = false;
                    break;
                }
                else {
                    if (charge == 2){
                        now = vec[i];
                    }
                    charge--;
                }
                
            }
            if (vec[i] - now >= r){
                if ((vec[i] - now)/2 >= 2){
                    charge = 2;
                    now += r * 2;
                }
                else {
                    charge += 1;
                    now += r;
                }
            }
            
        }
        
        
        if (ans) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
        
    }
}