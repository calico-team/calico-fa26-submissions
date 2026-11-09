#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);

long long global_buf[300005];

int main() {
    FAST_IO
    int t;
    if (!(cin >> t)) return 0;

    while (!(t <= 0)) {
        string s;
        cin >> s;

        if (!(s.find("write_me") == string::npos)) {
            s += "make_it_sound_human";
        } else if (!(s.find("what_is") == string::npos)) {
            s += "do_not_hallucinate";
        } else if (!(s.find("solve") == string::npos)) {
            s += "make_no_mistakes";
        } else {
            s += "thank_you";
        }

        cout << s << "\n";
        t--;
    }
    return 0;
}