#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 3e5 + 5;
const int LOG = 17, MAXB = 1<<LOG;
const int MOD = 998244353;
const int mod = 1e9 + 7;
const int K = 5e3+5;
bool is(string s, string t){
    if(t.size() > s.size())return false;
    int n = s.size();
    int m = t.size();
    s = ' ' + s;
    for(int i = 1 ; i <= n ; i ++){
        if(i + m - 1 > n)break;
        string u;   
        for(int j = i ; j <= i + m - 1 ; j ++){
            u += s[j];
        } 
        if(u == t)return true;
    }
    return false;
}
void solve(){
    string s;cin >> s;
    int n = s.size();
    string p = "write_me";
    string q = "what_is";
    string r = "solve";
    if(is(s, p)){
        s += "make_it_sound_human";
    }
    else if(is(s, q)){
        s += "do_not_hallucinate";
    }
    else if(is(s, r)){
        s += "make_no_mistakes";
    }
    else{
        s += "thank_you";
    }
    cout << s << '\n';
}
signed main(){
    ios_base::sync_with_stdio(0); //DO NOT USE THIS IN INTERACTIVE
    cin.tie(0), cout.tie(0);
    cout << fixed<<setprecision(9);
    int t = 1;
    cin >> t;
    while(t --){
        solve();
    }
}
