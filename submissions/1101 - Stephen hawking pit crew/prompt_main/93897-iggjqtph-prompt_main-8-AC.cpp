#include <iostream>
using namespace std;
int main(){
    int x;
    string a = "write_me";
    string b= "what_is";
    string c="solve";
    cin >> x;
    for(int i=0; i<x; i++){
        string s;
        cin >> s;
        if(s.find(a)!=string::npos){
            s+="make_it_sound_human";
        }else{
            if(s.find(b)!=string::npos){
            s+="do_not_hallucinate";
        }else{
         if(s.find(c)!=string::npos){
            s+="make_no_mistakes";
        }else{
            s+="thank_you";
        }   
        }
        }
        cout << s << endl;
    }

}           