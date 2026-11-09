#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int MAX = 2e5 +5, MOD = 2e9 +7, MKX = 1e5 +4;
const ll MTX = 1e18 +1;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;

        int a[MKX];
        for(int i=0; i<n; i++){
            cin >> a[i];
        }

        bool found = true;
        int x1=0, x2=0;
        for(int i=0; i<n; i++){
            if(a[i]>=x1){
                x1 = a[i] + k;
            }

            else if(a[i]>=x2){
                x2 = a[i] + k + max(0, x1 - a[i]);
            }

            else found = false;
        }

        if(found) cout << "YES\n";
        else cout << "NO\n";
    }
    
    return 0;
}