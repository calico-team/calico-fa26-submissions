#include <iostream>
#include <string>
using namespace std;

string solve(string A) {
    if (A.find("write_me") != string::npos) {
        return A + "make_it_sound_human";
    } else if (A.find("what_is") != string::npos) {
        return A + "do_not_hallucinate";
    } else if (A.find("solve") != string::npos) {
        return A + "make_no_mistakes";
    } else {
        return A + "thank_you";
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        string S;
        cin >> S;
        cout << solve(S) << "\n";
    }
    return 0;
}