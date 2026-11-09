#include <bits/stdc++.h>

using namespace std;

void solve(){
    int n, r; cin >> n >> r;
    int smokes_left = 2, last_recharge = 0;
    bool ok = false;
    for (int i = 0; i < n; i++){
        int x; cin >> x;
        if (ok) continue;
        if (last_recharge + r <= x) {
            smokes_left = min(2, smokes_left+1);
            last_recharge = last_recharge + r;
        }
        if (last_recharge + r <= x){
            smokes_left = min(2, smokes_left+1);
            last_recharge = last_recharge + r;
        }
        if (smokes_left == 2) last_recharge = x;
        else if (smokes_left == 0){
            cout << "NO\n";
            ok = true;
        }
        smokes_left--;
    }
    if (ok) return;
    cout << "YES\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while (t--){
        solve();
    }
    return 0;
}