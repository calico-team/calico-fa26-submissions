#include <iostream>
#include <string>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        if (s.find("write_me") != string::npos) cout << s << "make_it_sound_human\n";
        else if (s.find("what_is") != string::npos) cout << s << "do_not_hallucinate\n";
        else if (s.find("solve") != string::npos) cout << s << "make_no_mistakes\n";
        else cout << s << "thank_you\n";
    }
}
