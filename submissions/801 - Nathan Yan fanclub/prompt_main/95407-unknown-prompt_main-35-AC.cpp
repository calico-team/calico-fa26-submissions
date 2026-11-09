#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
#define inf 1000000000000000LL
#define mod 1000000007LL
#define FOR(i,a,b) for(int i = a; i < b; i++)

void solve() {
    string s;
    cin >> s;
    ll n = s.size();
    string a = "write_me";
    string b = "what_is";
    string c = "solve";
    auto v = s.find(a);
    auto v2= s.find(b);
    auto v3 = s.find(c);
    if (v >= 0 && v < n){
        s += "make_it_sound_human";
    }
    else if (v2 >= 0 && v2 < n){
        s += "do_not_hallucinate";
    }
    else if (v3 >= 0 && v3 < n){
        s+= "make_no_mistakes";
    }
    else{
        s+="thank_you";
    }
    cout << s << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll t = 1;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}