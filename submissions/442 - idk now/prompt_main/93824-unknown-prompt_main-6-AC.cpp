#include<bits/stdc++.h>
using namespace std;
using std::cout;
#define int long long

void q1() {
    string s; cin>>s;
    for (int i=0; i+8<s.size(); i++) {
        if (s.substr(i, 8)=="write_me") {
            cout<<s<<"make_it_sound_human\n";
            return;
        }
    }
    for (int i=0; i+7<s.size(); i++) {
        if (s.substr(i, 7)=="what_is") {
            cout<<s<<"do_not_hallucinate\n";
            return;
        }
    }
    for (int i=0; i+5<s.size(); i++) {
        if (s.substr(i, 5)=="solve") {
            cout<<s<<"make_no_mistakes\n";
            return;
        }
    }
    cout<<s<<"thank_you\n";
}

signed main() {
    ios::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0);
    int TC=1; cin>>TC;
    while (TC--) q1();
    return 0;
}