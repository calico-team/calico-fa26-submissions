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
            continue;
        }
        if (s.find("what_is")!=string::npos) {
            s+="do_not_hallucinate";
            continue;
        }
        if (s.find("solve")!=string::npos) {
            s+="make_no_mistakes";
            continue;
        }
        else
            s+="thank_you";
        cout << s << endl;
    }
    return 0;
}