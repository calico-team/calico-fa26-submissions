#include <iostream>
#include <string>
using namespace std;

int main() {
    int testcase;
    cin >> testcase;

    while (testcase--) {
        string string;
        cin >> string;

        if (string.find("write_me") != string::npos) {
            string += "make_it_sound_human";
        }
        else if (string.find("what_is") != string::npos) {
            string += "do_not_hallucinate";
        }
        else if (string.find("solve") != string::npos) {
            string += "make_no_mistakes";
        }
        else {
            string += "thank_you";
        }

        cout << string << '\n';
    }

    return 0;
}
