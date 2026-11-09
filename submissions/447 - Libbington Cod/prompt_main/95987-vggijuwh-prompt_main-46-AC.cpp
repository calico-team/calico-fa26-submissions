#include <iostream>
#include <string>

using namespace std;

int main() {
    int T; 
    cin >> T; 

    for (int t = 0; t < T; t++) {
    string S; 
    cin >> S;

    if (S.find("write_me") < S.length()) {
        cout << S << "make_it_sound_human";

    }

    else if (S.find("solve") < S.length()){
        cout << S << "make_no_mistakes";

    }

    else if (S.find("what_is") < S.length()){
        cout << S << "do_not_hallucinate";
    }

    else {
        cout << S << "thank_you";
    }

    cout << "\n"; 


    }
    return 0;
}