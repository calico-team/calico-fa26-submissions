#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fu(i,a,b) for(int i=(a);i<=(b);i++)
#define fd(i,a,b) for(int i=(a);i>=(b);i--)
#define V vector 
#define sz(x) (int)(x).size()

void solve() {
    string s;
    cin>>s;
    int n=sz(s);
    fu(i,0,n-8) {
        if(s.substr(i, 8)=="write_me") {
            s+="make_it_sound_human";
            cout<<s<<'\n';
            return;
        } 
    }
    fu(i,0,n-7) {
        if(s.substr(i,7)=="what_is") {
            cout<<s+"do_not_hallucinate\n";return;
        }
    }
    fu(i,0,n-5) {
        if(s.substr(i,5)=="solve") {
            cout<<s+"make_no_mistakes\n";
            return;
        }
    }
    cout<<s+"thank_you\n";
    return;
}
signed main() {
    int t;
    cin>>t;
    while(t--) {
        solve();
    }
}