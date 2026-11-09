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

void tanya(string &ans){
    cout << ans << endl;
    string v;cin>>v;
    ans = v;
}

int main(){

    // sheesh

    string dump;
    CF{
        int n,k;cin>>n>>k;
        vector<char> a(k);
        for(auto &aa : a) cin>>aa;

        string ans(n, '_');
        for(auto aa : a){
            bool ok = 0;
            for(int i = 0; i < n; i++){
                if(ans[i] == '_'){
                    ans[i] = aa;
                    ok = 1;
                }
            }

            tanya(ans);
            if(ans == "CORRECT") break;
        }
    }

    xingqiu
}
