#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        std::string s; cin >> s;
        if (s.find("write_me") != std::string::npos) {
            s += "make_it_sound_human";
        } else if (s.find("what_is") != std::string::npos) {
            s += "do_not_hallucinate";
        } else if (s.find("solve") != std::string::npos) {
            s += "make_no_mistakes";
        } else {
            s += "thank_you";
        }
        cout << s << endl;
    }
    return 0;
}