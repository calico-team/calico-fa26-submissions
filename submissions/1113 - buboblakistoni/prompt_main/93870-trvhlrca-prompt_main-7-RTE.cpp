#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;

void solve() {
  string S;
  cin >> S;
  bool b1 = false, b2 = false, b3 = false;
  
  for (int i = 0; i < S.size() - 7; i++) {
    string s2 = "";
    for (int j = 0; j < 8; j++) {
      s2 += S[i + j];
    }
    if (s2 == "write_me") {
      b1 = true;
      break;
    }
  }
  for (int i = 0; i < S.size() - 6; i++) {
    string s2 = "";
    for (int j = 0; j < 7; j++) {
      s2 += S[i + j];
    }
    if (s2 == "what_is") {
      b2 = true;
      break;
    }
  }
  for (int i = 0; i < S.size() - 4; i++) {
    string s2 = "";
    for (int j = 0; j < 5; j++) {
      s2 += S[i + j];
    }
    if (s2 == "solve") {
      b3 = true;
      break;
    }
  }

  if (b1) {
    cout << S + "make_it_sound_human" << '\n';
  }
  else if (b2) {
    cout << S + "do_not_hallucinate" << '\n';
  }
  else if (b3) {
    cout << S + "make_no_mistakes" << '\n';
  }
  else {
    cout << S + "thank_you" << '\n';
  }
  return;
}

int main() {
  fastio;
  int T;
  cin >> T;
  while (T--) {
    solve();
  }
}