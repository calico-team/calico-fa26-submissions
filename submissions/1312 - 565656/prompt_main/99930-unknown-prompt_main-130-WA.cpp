#include <iostream>

using namespace std;

int main()
{
  int t;
  cin >> t;
  while (t--)
  {
    string s = "";
    cin >> s;
    if(s.find("write_me"))
    {
      s += "make_it_sound_human";
    }
    else if (s.find("what_is"))
    {
      s += "do_not_hallucinate";
    }
    cout << s << " ";
  }
  return 0;
}

