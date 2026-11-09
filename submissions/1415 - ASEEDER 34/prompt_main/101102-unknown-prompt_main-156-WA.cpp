#include <string.h>
#include <iostream>
#include <random>
using namespace std;

int t;

string S;

string Guess(){
    cin>>S;
    int a=S.length();
    a -= 9;
    for (int i=0;i<a ;i++){

        if(S[i]=='w' && (i==0 || S[i-1]=='_')){
           
            if(S.substr(i,8)=="write_me"){
                
                return S+"make_it_sound_human";
            }
            if(S.substr(i,7)=="what_is"){
                return S+"do_not_hallucinate";
            }
        }

        if(S[i]=='s'&& (i==0 || S[i-1]=='_')){
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
