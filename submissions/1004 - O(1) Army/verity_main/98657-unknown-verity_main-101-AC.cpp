#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests;
    if (!(cin >> tests)) return 0;
    while (tests--) {
        int n, k;
        cin >> n >> k;
        vector<char> alphabet(k);
        for (char &letter : alphabet) cin >> letter;
        string known(n, '_');
        for (char letter : alphabet) {
            string guess = known;
            for (char &position : guess)
                if (position == '_') position = letter;
            cout << guess << endl;
            string reply;
            if (!(cin >> reply) || reply == "-1") return 0;
            if (reply == "CORRECT") break;
            known = reply;
        }
    }
}
