#include <bits/stdc++.h>
using namespace std;

int main() {
    int tst; cin >> tst;
    while(tst--){
        string prompt; cin >> prompt;
        bool cnt=true;
        int s=size(prompt);
        for(int i=0;i<s;i++){
            if(i<s-7 && prompt.substr(i,8)=="write_me"){
                cout << prompt << "make_it_sound_human" << endl;
                cnt=false;
            }
            else if(i<s-6 && prompt.substr(i,7)=="what_is"){
                cout << prompt << "do_not_hallucinate" << endl;
                cnt=false;
            }
            else if(i<s-4 && prompt.substr(i,5)=="solve"){
                cout << prompt << "make_no_mistakes" << endl;
                cnt=false;
            }
            else if(i==s-1 && cnt) cout << prompt << "thank_you" << endl;
        }
    }
}
