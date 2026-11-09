#include <iostream>
#include <string>
using namespace std;

string solve(const string& s) {
    if (s.find("write_me") != string::npos) return s + "make_it_sound_human";
    if (s.find("what_is")  != string::npos) return s + "do_not_hallucinate";
    if (s.find("solve")    != string::npos) return s + "make_no_mistakes";
    return s + "thank_you";
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        cout << solve(s) << "\n";
    }
    return 0;
}
