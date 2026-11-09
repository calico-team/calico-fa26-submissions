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
        ll N, K;
        cin >> N >> K;
        vector<ll> X(N);
        vector<ll> Y(N);
        vector<ll> Z(N);
        vector<char> dir(N);
        for(ll i = 0; i < N; i++){
            cin >> X[i] >> Y[i] >> Z[i] >> dir[i];
        }
        ll count = 0;
        for(ll i = 0; i < K; i++){
            set<pair<ll,ll>> plane;
            for(ll i = 0; i < N; i++){
                plane.insert({X[i],Y[i]});
            }
            count += plane.size();
            for(ll i = 0; i < N; i++){
                if(dir[i] == 'E'){
                    X[i] ++;
                }else{
                    Y[i] ++;
                }
            }
        }
        cout << count << endl;
    }

}