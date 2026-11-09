#include <iostream>
#include <string>

using namespace std;

int main() {
    int t;
    cin >> t;
    
    for(int i = 0; i < t; i++) {
        string s;
        cin >> s;
        
        if (s.find("write_me") != -1) {
            s = s + "make_it_sound_human";
        }
        else if (s.find("what_is") != -1) {
            s = s + "do_not_hallucinate";
        }
        else if (s.find("solve") != -1) {
            s = s + "make_no_mistakes";
        }
        else {
            s = s + "thank_you";
        }
        
        cout << s << endl;
    }
    
    return 0;
}