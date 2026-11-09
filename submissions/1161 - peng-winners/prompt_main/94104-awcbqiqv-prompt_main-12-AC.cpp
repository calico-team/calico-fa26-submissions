#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<string> sentences;
string sentence;
int N;
int main()
{
  cin.tie(0);
  cin.sync_with_stdio(false);
  cin >> N;

  while (N--)
  {
    cin >> sentence;

    if (sentence.find("write_me") != string::npos)
      sentence += "make_it_sound_human";
    else if (sentence.find("what_is") != string::npos)
      sentence += "do_not_hallucinate";
    else if (sentence.find("solve") != string::npos)
      sentence += "make_no_mistakes";
    else
      sentence += "thank_you";

    sentences.push_back(sentence);
  }

  for (string x : sentences)
  {
    cout << x << "\n";
  }
  return 0;
}