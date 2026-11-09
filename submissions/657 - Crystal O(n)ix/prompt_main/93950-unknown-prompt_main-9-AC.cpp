// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
	int t; cin >> t;
    while (t-- > 0) {
        string s;
        cin >> s;
        if (s.find("write_me") != string::npos) {
            cout << s << "make_it_sound_human" << endl;
        }
        else if (s.find("what_is") != string::npos) {
            cout << s << "do_not_hallucinate" << endl;
        }
        else if (s.find("solve") != string::npos) {
            cout << s << "make_no_mistakes" << endl;
        }
        else {
            cout << s << "thank_you" << endl;
        }
    }
}
