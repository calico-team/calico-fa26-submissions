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
  cin.tie(0);

  int t;
  cin >> t;
  while (t--) {
    int n, r;
    cin >> n >> r;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
    }
    pair<int, int> last = {-1000, 1};
    int last2 = -1000;
    bool found = false;
    vector<bool> slots = {true, true};
    int time = 0;
    for (int i = 0; i < n; ++i) {
      time = a[i];
      if (time-last.first >= r) {
        slots[0] = true;
        last.first = last2;
        last.second = 2;
      }

      if (slots[0] == true) {
        slots[0] = false;
        last.first = time;
        last.second = 1;
      } else if (slots[1] == true) {
        slots[1] = false;
        last2 = time;
      } else {
        cout << "NO" << '\n';
        found = true; 
        break;
      }
      // cout << slots[0] << slots[1] << '\n';
      // cout << last << '\n';
      

    }
    if (!found) {
      cout << "YES" << '\n';
    }
  }
  return 0;
}