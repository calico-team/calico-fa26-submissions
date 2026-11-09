// Question:
// 1: We are given N test cases
// 2: Each test case has a string that may contain some key words
// 3: If there are specific key words found, special strings need to be added at the back
// 4: Print Each of the final string

// Plan:
// 1: Read the number of test cases and grab each test case
// 2: If it has substring write_me, add make_it_sound_human and break
// 3: If it has substring what_is, add do_not_hallucinate and break
// 4: If it has substring solve, add make_no_mistakes and break
// 5: If it has nothing, add thank_you and break

// Pseudocode:
// Read T
// Repeat T times:
//        read string
//        i = 0
//        while i < length of string:
//              if substring of string is "write_me":
//                 add make_it_sound_human
//                 print 
//                 break
//              else if substring of string is "what_is":
//                   add do_not_hallucinate
//                   print
//                   break
//              else if substring of string is "solve:":
//                   add make_no_mistake
//                   print
//                   break

// Code:
#include <iostream>
#include <string>

using namespace std;

int main() {

    // 1: I / O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // 2: Read the number of test cases
    int T;
    cin >> T;

    // 3: Going through each test case
    while (T--) {
        string S;
        cin >> S;

        // 4: Scan the string
        int i = 0;
        while (i < static_cast<int> (S.size())) {

            // 5: Check write_me
            if (S.substr(i, 8) == ("write_me")) {
                S += "make_it_sound_human";
                cout << S << '\n';
                break;
            }

            // 6: Check what_is
            else if (S.substr(i, 7) == ("what_is")) {
                S += "do_not_hallucinate";
                cout << S << '\n';
                break;
            }

            // 7: Check solve
            else if (S.substr(i, 5) == ("solve")) {
                S += "make_no_mistake";
                cout << S << '\n';
                break;
            }

            i++;

            if (i == static_cast<int> (S.size())) {
                S += "thank_you";
                cout << S << '\n';
                break;
            }
        }


    }

    return 0;
}