#include <bits/stdc++.h>
using namespace std;

void fast_io() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

int n;
string s;

int main() {
    fast_io();
    cin >> n;

    for (int i=0;i<n;i++) {
        cin >> s;
        int j = s.find("write_me");
        int k = s.find("what_is");
        int l = s.find("solve");

        if (j != string::npos) {
            cout << s << "make_it_sound_human";
        } else if (k != string::npos) {
            cout << s << "do_not_hallucinate";
        } else if (l != string::npos) {
            cout << s << "make_no_mistakes";
        } else {
            cout << s << "thank_you";
        }
        cout << "\n";
    }

    return 0;
}