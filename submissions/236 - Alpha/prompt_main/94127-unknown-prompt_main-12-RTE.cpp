#define IN "input.txt"
#define OUT "output.txt"
#include <bits/stdc++.h>
using namespace std;
int main() {
    string d = __FILE__;
    d = d.substr(0, d.find_last_of("/\\") + 1);
    if (!freopen((d + IN).c_str(), "r", stdin) || !freopen((d + OUT).c_str(), "w", stdout)) {cerr << "can't open input/output file\n";return 1;}
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