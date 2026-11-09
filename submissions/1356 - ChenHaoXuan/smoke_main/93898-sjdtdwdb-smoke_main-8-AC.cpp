#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
typedef long long ll;

void solve()
{
    int n , r;cin>>n>>r;
    vector<ll>v(n);
    for(int i=0;i<n;i++)cin>>v[i];
    bool flag = true;
    ll x = 0, y =0;
    for(int i =0;i<n;i++){
        if(flag){
            if(x > y)swap(x, y);
            if(x <= v[i])x = max(v[i], y) + r;
            else flag = false;
        }
    }
    if(flag) cout << "Yes" << "\n";
    else cout << "No" << "\n"; 
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t; cin>>t;
    while(t--) solve();
    return 0;
}