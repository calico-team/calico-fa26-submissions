#include <iostream>
using namespace std;

string solve(string S) {
    if (S.find("write_me") != string::npos){
        S += "make_it_sound_human";
    } else if (S.find("what_is") != string::npos){
        S += "do_not_hallucinate";
    } else if (S.find("solve") != string::npos){
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