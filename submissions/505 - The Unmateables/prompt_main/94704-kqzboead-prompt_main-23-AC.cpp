#include <bits/stdc++.h>
#include <iomanip>
#include <queue>
using namespace std;
using ll=long long;
using db=double;
const ll N=40005;
const ll M=1000'005;
const ll MOD=1e9+7;
const ll INF=1e18;
using pr=pair<ll,ll>;
using tp=tuple<ll,ll,ll>;



void solve(){
 ll n; cin >> n;
 string a="write_me", b="what_is", c="solve";
 string p="make_it_sound_human", q="do_not_hallucinate", r="make_no_mistakes",t="thank_you";
 for(int i=0;i<n;i++){
  string s; cin >> s;
  if(s.find(a)!=string::npos) s+=p;
  else if(s.find(b)!=string::npos) s+=q;
  else if(s.find(c)!=string::npos) s+=r;
  else s+=t;
  cout << s << "\n";
 }
}
 


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll t=1;
    while(t--) solve();
}