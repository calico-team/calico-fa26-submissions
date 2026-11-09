#include <iostream>

using namespace std;

/*
 * Output the result of adding a certain string to the end of a prompt.
 *
 * S: Original prompt
 */
string solve(string S) {

    if (S.find("write_me") < S.length()) {

        S += "make_it_sound_human";

    }

    else if (S.find("what_is") < S.length()) {

        S += "do_not_hallucinate";

    }

    else if (S.find("solve") < S.length()) {

        S += "make_no_mistakes";

    }

    else {

        S += "thank_you";

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
