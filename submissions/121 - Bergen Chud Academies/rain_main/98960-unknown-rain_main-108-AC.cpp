#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<ll, ll>;
#define pb push_back
const int N = 200010;
pii a[N];
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while(T--){
        int n;
        ll k;
        cin >> n >> k;
        vector<pii> east;
        vector<pii> north;
        for(int i = 1; i <= n; i++){
            cin >> a[i].first >> a[i].second;
            int z;
            cin >> z;
            char type;
            cin >> type;
            if(type == 'E'){
                east.push_back({a[i].first + a[i].second, a[i].first});
            }else{
                north.push_back({a[i].first + a[i].second, a[i].first});
            }
        }
        sort(east.begin(), east.end());
        sort(north.begin(), north.end());
        ll ans = k * n;
        for(auto i : north){
            int s = i.first;
            int x = i.second;
            auto l = lower_bound(east.begin(), east.end(), pii{s, x - k + 1});
            auto r = upper_bound(east.begin(), east.end(), pii{s, x});
            ans -= r - l;
        }
        cout << ans << endl;
    }
    return 0;
}