#include <iostream>
#include <string>
using namespace std;

string append(string s1, string s2)
{
    string res = s1;
    for(int i = 0; i < s2.length(); i++)
    {
        res += s2[i];
    }
    return res;
}
bool contain(string s1, string s2)
{
    bool good;
    for(int i = 0; i < s2.length()-s1.length()+1; i++)
    {
        good = true;
        for(int j = 0; j < s1.length(); j++)
        {
            if (!(s1[j] == s2[i+j]))
            {
                good = false;
                break;
            }
        }
        if(good == true)
        {
            break;
        }       
    }
    return good;
}
int main()
{
    int n;
    cin >> n;
    for(int i = 0; i <n;i++)
    {
        bool w = false;
        string s;
        cin >> s;
        if((s.length() > 7) && contain("write_me", s))
        {
            cout << append(s,"make_it_sound_human") << endl;
            w = true;
        }
        if((s.length() > 6) && contain("what_is",s))
        {
            cout << append(s,"do_not_hallucinate") << endl;
            w = true;
        }
        if((s.length() > 4) && contain("solve", s))
        {
            cout << append(s, "make_no_mistakes") << endl;
            w = true;
        }
        if(w == false)
        {
            cout << append(s, "thank_you") << endl;
            w = true;
        }
    }
}
