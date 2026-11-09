#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

struct Drone{
    int sum, x;
    char d;
};

void solve(){
    //if gets blocked then n*k then -1
    //only blokc when dif dir
    ll n, k;
    cin >> n >> k;
    vector<Drone> a(n);
    for(int i = 0; i < n; i++){
        int x, y, z; 
        char d;
        cin >> x >> y >> z >> d;
        a[i] = {x + y, x, d};
    }
    sort(a.begin(), a.end(), [](Drone& a, Drone& b){
        if(a.sum != b.sum) return a.sum < b.sum;
        return a.x < b.x;
    });
    //now js group with same cord
    ll ans = 1LL * n *k;
    for(int i = 0; i < n;){
        int j = i;
        while(j < n && a[j].sum == a[i].sum) j++;
        int l = i;
        ll cnt = 0;
        for(int r = i; r < j; r++){
            while(l < r && a[r].x - a[l].x >= k){
                if(a[l].d == 'E'){
                    cnt--;
                }
                l++;
            }
            if(a[r].d == 'N'){
                ans -= cnt;
            }else{
                cnt++;
            }
        }
        i = j;
    }
    cout<<ans<<endl;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin >> t;
    while(t--) solve();
}