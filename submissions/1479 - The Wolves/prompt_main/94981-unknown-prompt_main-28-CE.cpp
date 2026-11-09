// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

void solve() {
    
    string s; cin>>s;
    int place=0;
    string phrase1="write_me";
    string phrase2="what_is";
    string phrase3="solve";

if(s.contains(phrase1)){
  s+="make_it_sound_human";
}else if(s.contains(phrase2)){
    s+="do_not_hallucinate";
}else if(s.contains(phrase3)){
    s+="make_no_mistakes";
}else{
    s+="thank_you";
}
cout<<s<<"\n";
}


int main() {

    int tc; 
    cin >> tc;
    for (int i = 0; i < tc; i++) {
        solve();
    }



    return 0;
}
