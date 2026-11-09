#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        string s;
        cin>>s;
        if(s.find("write_me")!=string::npos){
            s+="make_it_sound_human";
        }else if(s.find("what_is")!=string::npos){
            s+="do_not_hallucinate";
        }else if(s.find("solve")!=string::npos){
            s+="make_no_mistakes";
        }else{
            s+="thank_you";
        }
        for(int i=0;i<=s.length()-1;i++){
            printf("%c",s[i]);
        }
        printf("\n");
    }
    return 0;
}