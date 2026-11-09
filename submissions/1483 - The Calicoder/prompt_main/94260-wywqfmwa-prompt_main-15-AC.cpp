// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;

    for (int t = 0; t < T; t++) {
        string S;
        cin >> S;

        string newStr = S;

        if (S.find("write_me") != string::npos) {
            newStr.append("make_it_sound_human");
        } else if (S.find("what_is") != string::npos) {
            newStr.append("do_not_hallucinate");
        } else if (S.find("solve") != string::npos) {
            newStr.append("make_no_mistakes");
        } else {
            newStr.append("thank_you");
        }

        cout << newStr << endl;
    }
}
