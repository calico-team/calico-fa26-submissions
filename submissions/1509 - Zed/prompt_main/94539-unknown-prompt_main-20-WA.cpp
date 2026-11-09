#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main()
{
    int tc;
    cin >> tc;

    while (tc--)
    {
        string prompt;
        cin >> prompt;

        if (prompt.find("write_me") != string::npos)
        {
            prompt += "make_it_soung_human";
        }
        else if (prompt.find("what_is") != string::npos)
        {
            prompt += "do_not_hallucinate";
        }
        else if (prompt.find("solve") != string::npos)
        {
            prompt += "make_no_mistakes";
        }
        else
        {
            prompt += "thank_you";
        }

        cout << prompt << "\n";
    }
    return 0;
}
