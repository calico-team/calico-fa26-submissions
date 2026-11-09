#include <bits/stdc++.h>
using namespace std;

void solve(){
   string s;
   cin>>s;
   bool found=false;
   string temp;
   const char* str[]={"write_me","what_is","solve"};

    size_t position = s.find(str[0]);
    if (position != std::string::npos) {
            temp="_make_it_sound_human";
            found=true;
    } 
    position = s.find(str[1]);
    if (position != std::string::npos) {
            temp="_do_not_hallucinate";
            found=true;
    } 
    position = s.find(str[2]);
    if (position != std::string::npos) {
            temp="_make_no_mistakes";
            found=true;
    } 
    if(!found)temp="_thank_you";
    s+=temp;
    cout<<s<<'\n';   
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t = 1;
    cin >> t; 
    while (t--) {
        solve();
    }
    
    return 0;
}