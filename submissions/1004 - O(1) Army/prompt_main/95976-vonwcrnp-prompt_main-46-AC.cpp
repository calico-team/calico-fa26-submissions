#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests;
    cin >> tests;
    while (tests--) {
        string prompt;
        cin >> prompt;
        cout << prompt;
        if (prompt.find("write_me") != string::npos) cout << "make_it_sound_human";
        else if (prompt.find("what_is") != string::npos) cout << "do_not_hallucinate";
        else if (prompt.find("solve") != string::npos) cout << "make_no_mistakes";
        else cout << "thank_you";
        cout << '\n';
    }
}
