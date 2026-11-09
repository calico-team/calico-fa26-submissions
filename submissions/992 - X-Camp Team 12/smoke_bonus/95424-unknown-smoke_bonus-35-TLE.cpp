#include <bits/stdc++.h>
using namespace std;
void solve(){
    int n;
    long long r;
    cin >> n >> r;
    int charges = 2;
    long long next_recharge = -1;
    for (int i = 0; i < n; i++){
        long long t;
        cin >> t;
        while (charges < 2 && next_recharge <= t){
            charges++;
            if (charges < 2) next_recharge += r;
        }
        if (charges == 0){
            for (int j = i + 1; j < n; j++) cin >> t;
            cout << "NO" << endl;
            return;
        }
        charges--;
        if (charges == 1){
            next_recharge = t + r;
        }
    }
    cout << "YES" << endl;
}
int main(){
    int T;
    cin >> T;
    while (T--) solve();
    return 0;
}