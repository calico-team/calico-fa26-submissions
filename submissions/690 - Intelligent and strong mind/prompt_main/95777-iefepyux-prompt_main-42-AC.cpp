
#include<iostream>
#include<string>
using namespace std;

bool checksubstring(string original, string substring)
{
    int counter = 0;

    for(int i = 0; i < original.length(); i++)
    {
        if(original[i] == substring[counter])
        {
            counter++;

            if(counter == substring.length())
            {
                return true;
            }
        }
        else
        {
            if(original[i] == substring[0])
                counter = 1;
            else
                counter = 0;
        }
    }

    return false;
}

int main()
{
    int TestCases;
    cin >> TestCases;
    cin.ignore();

    while(TestCases--)
    {
        string original;

        getline(cin, original);

        string substring1 = "write_me";
        string substring2 = "what_is";
        string substring3 = "solve";

        if(checksubstring(original, substring1))
        {
            original = original + "make_it_sound_human";
        }
        else if(checksubstring(original, substring2))
        {
            original = original + "do_not_hallucinate";
        }
        else if(checksubstring(original, substring3))
        {
            original = original + "make_no_mistakes";
        }
        else
        {
            original = original + "thank_you";
        }

        cout << original << endl;
    }

    return 0;
}
