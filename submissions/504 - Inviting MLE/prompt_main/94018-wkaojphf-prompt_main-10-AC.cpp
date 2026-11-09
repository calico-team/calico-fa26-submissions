#include <bits/stdc++.h>
using namespace std;
using ll= long long;
string solve(string& s){
    // we can search easy
    if(s.find("write_me")!=string::npos){
        return s+"make_it_sound_human";
    }
    else if(s.find("what_is")!=string::npos){
        return s+"do_not_hallucinate";
    }
    else if(s.find("solve")!=string::npos){
        return s+"make_no_mistakes";
    }
    else{
        return s+"thank_you";
    }
}
int main(){
    int t;
    cin>>t;
    while(t--){
        string s;
        cin>>s;
        cout<<solve(s)<<'\n';
    }
}
