#include <iostream>
#include <string>
using namespace std;

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        string s;
        cin >> s;
        
        bool add = false;
        
        for (int i = 0; i < s.length(); i++) {
            if (s.length() - i >= 8 && s.substr(i, 8) == "write_me") {
                s += "make_it_sound_human";
                add = true;
                break;
            } else if (s.length() - i >= 7 && s.substr(i, 7) == "what_is") {
                s += "do_not_hallucinate";
                add = true;
                break;
                break;
            } else if (s.length() - i >= 5 && s.substr(i, 5) == "solve") {
                s += "make_no_mistakes";
                add = true;
                break;
            }
        }
        
        if (!add) {
            s += "thank_you";
        }
        
        cout << s << endl;
    }
}