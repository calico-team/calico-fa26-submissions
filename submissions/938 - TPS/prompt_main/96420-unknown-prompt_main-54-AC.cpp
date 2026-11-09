#include <iostream>

using namespace std;

/*
 * Output the result of adding a certain string to the end of a prompt.
 *
 * S: Original prompt
 */
string solve(string S) {
    string newstring;
    if(S.find("write_me")!=string::npos){
        newstring=S+ "make_it_sound_human";
    }
    else if(S.find("what_is")!=string::npos){
         newstring=S+ "do_not_hallucinate";
    }
    else if(S.find("solve")!=string::npos){
          newstring=S+ "make_no_mistakes";
    }
    else{
          newstring=S+ "thank_you";
    }
    return  newstring;
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
