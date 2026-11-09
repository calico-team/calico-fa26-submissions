#include <bits/stdc++.h>
using namespace std;

int main () {
  ios_base::sync_with_stdio(0); cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n, k;
    cin >> n >> k;
    vector<char> A(k);
    for (auto& x: A) cin >> x;
    string ans(n, '_');
    bool found = 0;
    for (int i = 0; i < k; i++) {
      cout << string(n, A[i]) << endl;
      string res;
      cin >> res;
      if (res == "CORRECT") {
        found = 1;
        break;
      }
      for (int j = 0; j < n; j++) {
        if (res[j] != '_') ans[j] = res[j];
      }
    }
    if (!found) {
      cout << ans << endl;
      string res;
      cin >> res;
      assert(res == "CORRECT");
    }
  }
}
