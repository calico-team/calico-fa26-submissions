#include <iostream>
#include <string>
using namespace std;

int main()
{
    int my;
    cin >> my;
    while (my--)
    {
        string stri;
        cin >> stri;

        if (stri.find("write_me") != string::npos)
        {
            stri += "make_it_sound_human";
        }
        else if (stri.find("what_is") != string::npos)
        {
            stri += "do_not_hallucinate";
        }
        else if (stri.find("solve") != string::npos)
        {
            stri += "make_no_mistakes";
        }
        else
        {
            stri += "thank_you";
        }

        cout << stri << "\n";
    }
    return 0;
}