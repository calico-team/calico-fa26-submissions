#include <string.h>
#include <iostream>
using namespace std;
int t;

string S;

string Guess(){
    cin>>S;
    
    for (int i=0;i<S.length()-9 ;i++){

        if(S[i]=='w'){
           
            if(S.substr(i,8)=="write_me"){
                
                return S+"make_it_sound_human";
            }
            if(S.substr(i,7)=="what_is"){
                return S+"do_not_hallucinate";
            }
        }
        if(S[i]=='s'){
            if(S.substr(i,5)=="solve"){
                return S+"make_no_mistakes";
            }
        }
    }
    return S+"thank_you";
} 

int main(){

    cin>>t;
    for (int i=0;i<t; i++){
        cout<<Guess()<<endl;
    }
    return 0;

}
