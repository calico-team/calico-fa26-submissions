#include <iostream>
#include <string>
using namespace std;

int main() {
    string pat[3] = {"write_me", "what_is", "solve"};
    string ad[3] = {"make_it_sound_human", "do_not_hallucinate", "make_no_mistakes"};

    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        string add = "thank_you";
        bool found = false;
        for (int k = 0; k < 3 && !found; k++) {
            int n = pat[k].size();
            for (int i = 0; i + n <= (int)s.size(); i++) {
                if (s.substr(i, n) == pat[k]) {
                    add = ad[k];
                    found = true;
                    break;
                }
            }
        }
        cout << s + add << "\n";
    }
}