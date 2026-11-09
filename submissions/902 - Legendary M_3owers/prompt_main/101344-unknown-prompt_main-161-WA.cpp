#include <bits/stdc++.h>
using namespace std;

int main() {
cout<<"Enter prompt bro:"<<endl;
    string s;
    cin >> s;

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