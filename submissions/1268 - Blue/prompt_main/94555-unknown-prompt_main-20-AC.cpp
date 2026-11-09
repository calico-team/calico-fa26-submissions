#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while(t--){
        string s; cin >> s;
        int c = 0; int d = 0; int e = 0;
        for (int i = 0; i <= (int)s.size() - 8; i++) {
            if(s[i] == 'w' && s[i+1] == 'r' && s[i+2] == 'i' && s[i+3] == 't' && s[i+4] == 'e' && s[i+5] == '_' && s[i+6] == 'm' && s[i+7] == 'e'){c++; break;} //write_me
        }
        for (int i = 0; i <= (int)s.size() - 7; i++) {
            if(s[i] == 'w' && s[i+1] == 'h' && s[i+2] == 'a' && s[i+3] == 't' && s[i+4] == '_' && s[i+5] == 'i' && s[i+6] == 's'){d++; break;} //what_is
        }
        for (int i = 0; i <= (int) s.size() - 5; i++) {
            if(s[i] == 's' && s[i+1] == 'o' && s[i+2] == 'l' && s[i+3] == 'v' && s[i+4] == 'e'){e++; break;} //solve
        }
        if(c == 1){s += "make_it_sound_human"; cout << s << "\n";}
        else if(d == 1){s += "do_not_hallucinate"; cout << s << "\n";}
        else if(e == 1){s += "make_no_mistakes"; cout << s << "\n";}
        else{s += "thank_you"; cout << s << "\n";}
    }
}