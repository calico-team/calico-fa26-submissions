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
    int N, k;
    cin >> N >> k;
    vector<vector<int>> n;
    vector<vector<int>> e;
    for (int i = 0; i < N; ++i) {
      int xi, yi, zi;
      char dir;
      cin >> xi >> yi >> zi >> dir;
      if (dir == 'N') {
        n.push_back({xi, yi, zi});
      } else {
        e.push_back({xi, yi, zi});
      }
    }
    int cnt = 0;
    for (int i = 0; i < n.size(); ++i) {
      for (int j = 0; j < e.size(); ++j) {
        vector<int> nd = n[i];
        vector<int> ed = e[j];
        if (ed[1] - nd[1] > 0 and nd[0] - ed[0] > 0) {
          if (ed[1] - nd[1] < k and nd[0] - ed[0] < k) {
            if (ed[1] - nd[1] == nd[0] - ed[0]) {
              cnt++;
            } 
          }
        }
      }
    }
    cout << N * k - cnt << '\n';
  }
  return 0;
}