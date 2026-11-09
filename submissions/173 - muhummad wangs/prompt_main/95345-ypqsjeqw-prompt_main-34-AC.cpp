#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int cases = 0;
    cin >> cases;
    cin.ignore(1000, '\n');
    for (int _ = 0; _ < cases; ++_)
    {

        string s = "";
        cin >> s;

        if (s.back() != '_')
        {
            s += "_";
        }

        if (s.find("write_me") != string::npos)
        {

            s += "make_it_sound_human";
        }
        else if (s.find("what_is") != string::npos)
        {
            s += "do_not_hallucinate";
        }
        else if (s.find("solve") != string::npos)
        {
            s += "make_no_mistakes";
        }
        else
        {
            s += "thank_you";
        }

        cout << s << '\n';

        // REMEMBER TO CLEAN UP OUTPUT FOR SUBMISSION!!!
    }

    return 0;
}