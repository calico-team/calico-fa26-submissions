#include <bits/stdc++.h>
using namespace std;

enum Token { WRITE_ME, WHAT_IS, SOLVE, NONE };

Token solve(string s) {
  if (s.find("write_me") != string::npos) {
    return WRITE_ME;
  }
  if (s.find("what_is") != string::npos) {
    return WHAT_IS;
  }
  if (s.find("solve") != string::npos) {
    return SOLVE;
  }
  return NONE;
}

string parse_enum(Token t) {
  switch (t) {
  case WRITE_ME:
    return "make_it_sound_human";
  case WHAT_IS:
    return "do_not_hallucinate";
  case SOLVE:
    return "make_no_mistakes";
  }
  return "thank_you";
}

int main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    string S;
    cin >> S;
    cout << S + parse_enum(solve(S)) << '\n';
  }
}
