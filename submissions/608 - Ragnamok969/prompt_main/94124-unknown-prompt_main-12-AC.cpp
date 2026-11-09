#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll t; cin >> t;
    while (t--){
        string s; cin >> s;
        bool ch1 = false, ch2 = false, ch3 = false;
        string s1 = "write_me", s2 = "what_is", s3 = "solve";
        if (s.find(s1) != string::npos) ch1 = true;
        if (s.find(s2) != string::npos) ch2 = true;
        if (s.find(s3) != string::npos) ch3 = true;
        if (ch1) cout << s + "make_it_sound_human" << endl;
        else if (ch2) cout << s + "do_not_hallucinate" << endl;
        else if (ch3) cout << s + "make_no_mistakes" << endl;
        else cout << s + "thank_you" << endl; 
    }
}