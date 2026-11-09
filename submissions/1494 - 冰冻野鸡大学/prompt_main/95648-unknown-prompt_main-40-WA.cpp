#include <iostream>
#include <string>
using namespace std;
string solve(string s){
    if(s.find("write_me")!=true){
        return s + "make_it_sound_human";
    }else if(s.find("what_is")!=true){
        return s + "do_not_hallucinate";
    }else if(s.find("solve")!=true){
        return s+"make_no_mistakes";
    }else{
        return s+"thank_you";
    }
}

int main(){
    int t;
    cin>>t;
    while (t--){
        string s;
        cin>>s;
        cout<<solve(s)<<endl;
    }
    return 0;
}