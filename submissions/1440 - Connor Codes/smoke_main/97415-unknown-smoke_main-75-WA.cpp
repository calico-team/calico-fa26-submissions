#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    // freopen("XXXXXXX.in", "r", stdin);
    // freopen("XXXXXXX.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll T;
    cin >> T;
    while(T--){
        ll N, R;
        cin >> N >> R;
        vector<ll> nums(N);
        ll count = R*2;
        for(ll i = 0; i < nums.size(); i++){
            cin >> nums[i];
        }
        ll work = true;
        for(ll i = 0; i < N; i++){
            if(i == 0){
                count -= R;
            }
            if(i > 0){
                ll x = min(nums[i]-nums[i-1],R);
                count += x;
                count -= R;
            }
            if(count < 0){
                cout << "NO" << endl;
                work = false;
                break;
            }
           
        }
        if(work){
            cout << "YES" << endl;
        }
    }
}