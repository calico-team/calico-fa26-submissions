#include <iostream>

using namespace std;

/*
 * Output the result of adding a certain string to the end of a prompt.
 *
 * S: Original prompt
 */
string solve(string S) {
    string ans;
    bool human = false, do_not = false, solve = false, ty = false;
    if(S.size()>=8){
        for(int i = 0; i<S.size()-8; i++){
            if(S.substr(i, 8) == "write_me"){
                human = true;
            }
        }
    }   
    if(S.size()>=7){ 
        for(int i = 0; i<S.size()-7; i++){
            if(S.substr(i, 7) == "what_is"){
                do_not = true;
            }
        }
    }
    if(S.size()>=5){    
        for(int i = 0; i<S.size()-5; i++){
            if(S.substr(i, 5) == "solve"){
                solve = true;
            }
        }
    }    
    if(human == false && do_not == false && solve == false){
        ty = true;
    }
    if(human == true){
        ans = S + "make_it_sound_human";
        return ans;
    }
    if(do_not == true){
        ans = S + "do_not_hallucinate";
        return ans;
    }
    if(solve == true){
        ans = S + "make_no_mistakes";
        return ans;
    }
    if(ty == true){
        ans = S + "thank_you";
        return ans;
    }
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
