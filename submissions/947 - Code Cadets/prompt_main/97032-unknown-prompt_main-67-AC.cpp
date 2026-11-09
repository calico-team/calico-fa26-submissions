#include <iostream>

using namespace std;

/*
 * Output the result of adding a certain string to the end of a prompt.
 *
 * S: Original prompt
 */
string solve(string S) 
{
        if (S.find("write_me") != string::npos)
        {
            return S + "make_it_sound_human";
        }
        else if (S.find("what_is") != string::npos)
        {
            return S + "do_not_hallucinate";
        }
        else if (S.find("solve") != string::npos)
        {
           return S + "make_no_mistakes";
        }
        else
        {
            return S + "thank_you";
        }
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        string S;
        cin >> S;
        cout << solve(S) << '\n';
    }
}
