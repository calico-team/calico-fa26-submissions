//written by sarah
#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    string s;
    cin >> t;

    for (int i=0; i<t; i++) {
        cin >> s;
        if (s.find("write_me")!=string::npos) {
            s+="make_it_sound_human";
        }
        if (s.find("what_is")!=string::npos) {
            s+="do_not_hallucinate";
        }
        if (s.find("solve")!=string::npos) {
            s+="make_no_mistakes";
        }
        else
            s+="thank you";
        cout << s << endl;
    }
    return 0;
}