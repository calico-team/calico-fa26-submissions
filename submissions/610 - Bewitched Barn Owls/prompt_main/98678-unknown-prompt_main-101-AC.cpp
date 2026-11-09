#include <iostream>
#include <string>

using namespace std;
string a = "write_me";
string b = "what_is";
string c = "solve";
/*
 * Output the result of adding a certain string to the end of a prompt.
 *
 * S: Original prompt
 */
string solve(string S) {
    for(int i = 0; i < ((int)S.length()-5);i++){
        if(i+8 <= (int)S.length()){
            string subS = S.substr(i,8);
            if(subS.compare(a) == 0){
                return S + "make_it_sound_human"; 
            }
        }
        if(i+7 <= (int)S.length()){
            string subS = S.substr(i,7);
            if(subS.compare(b) == 0){
                return S + "do_not_hallucinate "; 
            }
        }
        string subS = S.substr(i,5);
        if(subS.compare(c) == 0){
            return S + "make_no_mistakes "; 
        }
    }
    return S + "thank_you";
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
