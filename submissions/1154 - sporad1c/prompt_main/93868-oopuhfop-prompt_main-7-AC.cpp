/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;

        if (s.find("write_me") != string::npos)
            s += "make_it_sound_human";
        else if (s.find("what_is") != string::npos)
            s += "do_not_hallucinate";
        else if (s.find("solve") != string::npos)
            s += "make_no_mistakes";
        else
            s += "thank_you";

        cout << s << '\n';
    }
    return 0;
}
