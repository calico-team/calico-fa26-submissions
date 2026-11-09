#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        if (s.contains("write_me")) {
            cout << s + "make_it_sound_human" << endl;
        }
        else if (s.contains("what_is")) {
            cout << s + "do_not_hallucinate" << endl;
        }
        else if (s.contains("solve")) {
            cout << s + "make_no_mistakes" << endl;
        }
        else {
            cout << s + "thank_you" << endl;
        }
    }
}