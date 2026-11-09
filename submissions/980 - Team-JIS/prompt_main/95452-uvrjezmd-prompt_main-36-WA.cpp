#include <bits/stdc++.h>
#include <string>
using namespace std;
int main(){
    int T; 
    cin>>T;
    while(T--){
        string S;
        cin>>S;

        if(S.find("write_me") != string::npos){
            S = S + "_make_it_sound_human";
        }
        else if(S.find("what_is") != string::npos){
            S = S + "_do_not_hallucinate";
        }
        else if(S.find("solve") != string::npos){
            S = S+ "_make_no_mistakes";
        }
        else{
            S = S +"_thank_you";
        }
        cout<< S << endl;
    }
    return 0;
}