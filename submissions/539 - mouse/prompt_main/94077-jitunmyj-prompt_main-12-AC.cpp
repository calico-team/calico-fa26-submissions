#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        if (s.find("write_me", 0) != string::npos) {
            s += "make_it_sound_human";
        }
        else if (s.find("what_is", 0) != string::npos) {
            s += "do_not_hallucinate";
        }
        else if (s.find("solve", 0) != string::npos) {
            s += "make_no_mistakes";
        }
        else {
            s += "thank_you";
        }
        cout << s << "\n";
    }
}