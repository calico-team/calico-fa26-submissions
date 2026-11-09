#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
using ll=long long;using pii=pair<int,int>;using pll=pair<ll,ll>;
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define fi first
#define se second
#define int long long
const ll INF=1e18;const int MOD=1e9+7;
void fast_io(){ios::sync_with_stdio(false);cin.tie(nullptr);}

void solve() {
    string s;cin>>s;cout<<s;
    if(s.find("write_me")!=string::npos){cout<<"make_it_sound_human";}
    else if(s.find("what_is")!=string::npos){cout<<"do_not_hallucinate";}
    else if(s.find("solve")!=string::npos){cout<<"make_no_mistakes";}
    else{cout<<"thank_you";}
    cout<<"\n";
}

signed main() {
    fast_io();

    int t = 1;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}