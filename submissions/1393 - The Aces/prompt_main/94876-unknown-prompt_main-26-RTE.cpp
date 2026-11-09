// Success consists of going from failure to failure without loss of enthusiasm.
// ad hoc ad hoc go away, come again another day
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <iostream>
#define int long long
#define double long double
#pragma GCC optimize("Ofast,unroll-loops")
using namespace std;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tt; cin >> tt;
    string s1="write_me";
    string s2="what_is";
    string s3="solve";
    while (tt > 0){
        string s; cin >> s;
        bool change = false;
        for (int i = 0; i <= s.size()-5; i++){
            if (s.substr(i,5)==s3){
                cout << s << "make_no_mistakes\n";
                change = true;
                break;
            }
        }
        for (int i = 0; i <= s.size()-7; i++){
            if (s.substr(i,7)==s2){
                cout << s << "do_not_hallucinate\n";
                change = true;
                break;
            }
        }
        for (int i = 0; i <= s.size()-8; i++){
            if (s.substr(i,8)==s1){
                cout << s << "make_it_sound_human\n";
                change = true;
                break;
            }
        }
        if(!change)cout << s << "thank_you\n";
        tt--;
    }
}