#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        if (s.find("write_me") != string::npos) s += "make_it_sound_human";
        else if (s.find("what_is") != string::npos) s += "do_not_hallucinate";
        else if (s.find("solve") != string::npos) s += "make_no_mistakes";
        else s += "thank_you";
        cout << s << "\n";
    }
}