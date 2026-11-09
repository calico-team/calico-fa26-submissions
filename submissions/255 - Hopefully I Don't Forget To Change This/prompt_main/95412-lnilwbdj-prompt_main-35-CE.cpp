#include <bits/stdc++.h>
using namespace std;
int main(){
    string s;
    cin >> s;
    if(s.contains("write_me")) cout << s + "make_it_sound_human";
    else if(s.contains("what_is")) cout << s + "do_not_hallucinate";
    else if(s.contains("solve")) cout << s + "make_no_mistakes";
    else cout << s + "thank_you";
}