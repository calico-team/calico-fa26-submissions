#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

void solve(){
    string s;cin>>s;
    cout<<s;
    for (int i=0;i<s.length()-7;i++){
        if (s.substr(i,8)=="write_me"){
            cout<<"make_it_sound_human\n";
            return;
        }
    }
    for (int i=0;i<s.length()-6;i++){
        if (s.substr(i,7)=="what_is"){
            cout<<"do_not_hallucinate\n";
            return;
        }
    }
    for (int i=0;i<s.length()-4;i++){
        if (s.substr(i,5)=="solve"){
            cout<<"make_no_mistakes\n";
            return;
        }
    }
    cout<<"thank_you\n";
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int t;cin>>t;
    while (t--)solve();
}
