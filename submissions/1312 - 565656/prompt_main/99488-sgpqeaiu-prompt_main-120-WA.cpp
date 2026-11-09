#include <iostream>

using namespace std;

int main()
{
  int t;
  cin >> t;
  while (t--)
  {
    string s;
    cin >> s;
    if(s.find("write_me"))
    {
      s += "make_it_sound_human";
    }
    cout << s << " ";
  }
  return 0;
}

