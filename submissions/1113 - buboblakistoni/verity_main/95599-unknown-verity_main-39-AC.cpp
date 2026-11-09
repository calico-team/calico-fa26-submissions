#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;

void solve() {
  int N, K;
  cin >> N >> K;
  vector<char> A(K);
  for (int i = 0; i < K; i++) {
    cin >> A[i];
  }

  string current_best = "";
  for (int i = 0; i < N; i++) {
    current_best += "_";
  }

  for (int i = 0; i < K; i++) {
    string guess = current_best;
    for (int j = 0; j < N; j++) {
      if (current_best[j] == '_') {
        guess[j] = A[i];
      }
    }
    cout << guess << endl;
    string feedback;
    cin >> feedback;
    if (feedback == "CORRECT") {
      return;
    }
    else {
      current_best = feedback;
    }
  }
}

int main() {
  fastio;
  int T;
  cin >> T;
  while(T--) {
    solve();
  }
}