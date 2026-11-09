
#include <iostream>
#include <string>
using namespace std;

int main() {

    int t ; cin >> t ;

    while(t--){
        string S;
        cin >> S;

    if (S.find("write_me") != string::npos) {
        S += "make_it_sound_human";
    }
    else if (S.find("what_is") != string::npos) {
        S += "do_not_hallucinate";
    }
    else if (S.find("solve") != string::npos) {
        S += "make_no_mistakes";
    }
    else {
        S += "thank_you";
    }

    cout << S << endl;


        }
    

    return 0;
}
