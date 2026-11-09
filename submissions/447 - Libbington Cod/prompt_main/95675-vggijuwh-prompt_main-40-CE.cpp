#include <iostream>
#include <string>

using namespace std;

int main() {
    int T; 
    cin >> T; 

    for (int t = 0; t < T; t++) {
    string S; 
    cin >> S;

    if (S.contains("write_me")) {
        cout << S << "make_it_sound_human";

    }

    else if (S.contains("solve")){
        cout << S << "make_no_mistakes";

    }

    else if (S.contains("what_is")){
        cout << S << "do_not_hallucinate";
    }

    else {
        cout << S << "thank_you";
    }

    cout << "\n"; 


    }
    return 0;
}