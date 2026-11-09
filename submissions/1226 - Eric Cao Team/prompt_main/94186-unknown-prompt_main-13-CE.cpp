#include <iostream>
using namespace std;

string solve(string S) {
    if (S.contains("write_me")){
        S += "make_it_sound_human";
    } else if (S.contains("what_is")){
        S += "do_not_hallucinate";
    } else if (S.contains("solve")){
        S += "make_no_mistakes";
    } else {
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