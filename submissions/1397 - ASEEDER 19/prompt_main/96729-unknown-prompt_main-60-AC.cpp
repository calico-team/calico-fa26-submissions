#include <iostream>
#include <cstring>
using namespace std;
string prompt(string s){
    string sub1 = "write_me";
    string sub2 = "what_is";
    string sub3 = "solve";
    if(s.find(sub1)!= std::string::npos){
        s += "make_it_sound_human";
    }
    else if(s.find(sub2)!= std::string::npos){
        s += "do_not_hallucinate";
    }
    else if(s.find(sub3)!= std::string::npos){
        s += "make_no_mistakes";
    }
    else{
        s+= "thank_you";
    }
    return s;
}

int main(){
    int n;
    cin >> n;
    for(int i=0; i<n; i++){
        string s;
        cin >> s;
        cout << prompt(s) << endl;
    }
    return 0;
}