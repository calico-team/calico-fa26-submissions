#include <bits/stdc++.h>
using namespace std;
int main(){
    /*
    write_me                make_it_sound_human
    what_is                 do_not_hallucinate
    solve                   make_no_mistakes

    thank_you
    */

    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        string s;
        cin >> s;
        bool add = false;
        if(s.length() >= 8){
            for(int j = 0; j < s.length() - 8; j++){
                if(s.length() >= 8 and s.substr(j, 8) == "write_me"){
                    s = s + "make_it_sound_human";
                    add = true;
                }
            }
        }
        if(s.length() >= 7){
            for(int j = 0; j < s.length() - 7; j++){
                if(s.length() >= 7 and s.substr(j, 7) == "what_is"){
                    s = s + "do_not_hallucinate";
                    add = true;
                }
            }
        }
        if(s.length() >= 5){
            for(int j = 0; j < s.length() - 5; j++){
                if(s.length() >= 5 and s.substr(j, 5) == "solve"){
                    s = s + "make_no_mistakes";
                    add = true;
                }
            }
        }
        if(!add){
            s = s + "thank_you";
        }
        cout << s << endl;
    }
    return 0;
}