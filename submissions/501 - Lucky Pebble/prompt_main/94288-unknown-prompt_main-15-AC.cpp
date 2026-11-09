#include <iostream>
#include <string>
using namespace std;

int main() {
    int T;
    string S;
    
    cin >> T;

    while (T--) {
        cin >> S;
        if (S.find("write_me") != string::npos) cout << S + "make_it_sound_human" << "\n";
        else if (S.find("what_is") != string::npos) cout << S + "do_not_hallucinate" << "\n";
        else if (S.find("solve") != string::npos) cout << S + "make_no_mistakes" << "\n";
        else cout << S + "thank_you" << "\n";
    }

    return 0;
}