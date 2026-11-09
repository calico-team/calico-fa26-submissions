#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define ull unsigned long long
#define pii pair<int, int>
#define pli pair<ll, int>
#define pll pair<ll, ll>
#define pb push_back
#define fi first
#define se second
#define cont continue
#define iMAXI 1e9
#define llMAXI 1e18
#define MOD7 1e9 + 7
#define MOD9 1e9 + 9
#define MODfft 998244353
#define decim(n) cout<<fixed<<setprecision(n)
#define CF int tt;cin>>tt;while(tt--)
#define sheesh ios::sync_with_stdio(0);cin.tie(0);
#define xingqiu return 0;

using namespace std;

int main(){

    sheesh

    CF{
        int n;cin>>n;
        ll r;cin>>r;
        vector<ll> a(n);
        for(auto &aa : a) cin>>aa;

        bool ok = 1;
        queue<ll> ucup;
        for(auto aa : a){
            while(!ucup.empty()){
                if(ucup.front() <= aa) ucup.pop();
                else break;
            }

            ll tt = aa;
            if(ucup.size() < 2) if(!ucup.empty()) tt = max(tt, ucup.front());
            else{
                ok = 0;
                break;
            }

            ucup.push(tt + r);
        }

        cout << (ok ? "YES" : "NO") << "\n";
    }

    xingqiu
}
