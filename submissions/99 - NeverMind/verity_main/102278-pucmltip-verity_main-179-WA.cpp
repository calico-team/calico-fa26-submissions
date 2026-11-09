#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <deque>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <climits>
#include <numeric>
#include <utility>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);

  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;
    vector<char> a(k);
    for (int i = 0; i < k; ++i) {
      cin >> a[i];
    }
    string ans(n, '_');
    for (int i = 0; i < k; ++i) {
      char letter = a[i];
      string guess(n, letter);
      cout << guess << endl;
      string feedback;
      cin >> feedback;
      for (int i = 0; i < k; ++i) {
        if (feedback[i] != '_') {
          ans[i] = feedback[i];
        }
      }
    cout << ans << endl;

    }
  }
  return 0;
}