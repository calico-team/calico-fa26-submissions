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
        string s;cin>>s;
        int n = s.size();

        pair<string, string> a[3] = {{"write_me", "make_it_sound_human "}, {"what_is", "do_not_hallucinate"}, {"solve", "make_no_mistakes"}};
        bool ok = 0;
        for(auto [x, app] : a){
            if(s.find(x) != string::npos){
                s += app;
                ok = 1;
                break;
            }
        }

        if(!ok) s += "thank_you";
        cout << s << "\n";
    }

    xingqiu
}
