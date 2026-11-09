//
// Created by User on 11/8/2026.
//
#include "bits/stdc++.h"
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int cases;
    cin>>cases;
    for (int what=0; what<cases; what++) {
        string s;
        cin>>s;
        for (int i=0; i<=s.size()-8; i++) {
            if (s.substr(i,8)=="write_me") {
                cout<<s<<"make_it_sound_human"<<"\n";
                goto here;
            }
        }
        for (int i=0; i<=s.size()-7; i++) {
            if (s.substr(i,7)=="what_is") {
                cout<<s<<"do_not_hallucinate"<<"\n";
                goto here;
            }
        }
        for (int i=0; i<=s.size()-5; i++) {
            if (s.substr(i,5)=="solve") {
                cout<<s<<"make_no_mistakes"<<"\n";
                goto here;
            }
        }
        cout<<s<<"thank_you"<<"\n";

        here:int x=0;
    }
}