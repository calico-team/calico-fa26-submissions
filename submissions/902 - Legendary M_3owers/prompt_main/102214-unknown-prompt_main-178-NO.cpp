#include <bits/stdc++.h>
using namespace std;

int main() {

    string s;
    cin >> s;

    if (s[0] >= '0' && s[0] <= '9') {
        return 0;
    }

    bool ck = (s.find("write_me") != string::npos);
    bool chk = (s.find("what_is") != string::npos);
    bool chek = (s.find("solve") != string::npos);

    if (ck == true) {
        cout << s << "make_it_sound_human";
    }
    else if (chk == true) {
        cout << s << "do_not_hallucinate";
    }
    else if (chek == true) {
        cout << s << "make_no_mistakes";
    }
    else {
        cout << s << "thank_you";
    }

    return 0;
}