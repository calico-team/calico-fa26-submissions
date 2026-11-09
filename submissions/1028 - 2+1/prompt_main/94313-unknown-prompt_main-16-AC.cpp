#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        bool one = 0, two = 0, three = 0;
        for (int i = 0; i < s.length(); i++) {
            if (i + 7 < s.length() && s.substr(i, 8) == "write_me") {
                one = 1;
            }
            if (i + 6 < s.length() && s.substr(i, 7) == "what_is") two = 1;
            else if (i + 4 < s.length() && s.substr(i, 5) == "solve") three = 1;
        }
        if (one) s += "make_it_sound_human";
        else if (two) s += "do_not_hallucinate";
        else if (three) s += "make_no_mistakes";
        else s += "thank_you";
        cout << s << endl;
    }
    
}
