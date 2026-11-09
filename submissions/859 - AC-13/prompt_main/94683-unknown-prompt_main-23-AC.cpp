#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    string c;
    while(t--){
        cin >> c;
        if(c.find("write_me") != string::npos){ 
            c.append("make_it_sound_human");
        } else if (c.find("what_is") != string::npos){
            c.append("do_not_hallucinate");
        } else if (c.find("solve") != string::npos){
            c.append("make_no_mistakes");
        } else {
            c.append("thank_you");
        }
        cout << c << "\n";
    }
    return 0;
}