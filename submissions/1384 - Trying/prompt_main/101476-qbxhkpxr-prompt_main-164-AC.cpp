#include <iostream>

using namespace std;

/*
 * Output the result of adding a certain string to the end of a prompt.
 *
 * S: Original prompt
 */
string solve(string S) {

    string s1 = "write_me";
    string s2 = "what_is";
    string s3 = "solve";

    if (S.find(s1) != string::npos) {
       S.append("make_it_sound_human");
    }
    else if (S.find(s2) != string::npos) {
       S.append("do_not_hallucinate");
    }

    else if (S.find(s3) != string::npos) {
        S.append("make_no_mistakes");
    }
    else{
        S.append("thank_you");
    }

    return S;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        string S;
        cin >> S;
        cout << solve(S) << '\n';
    }
}
