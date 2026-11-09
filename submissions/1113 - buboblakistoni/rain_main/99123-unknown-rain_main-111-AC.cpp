#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;

typedef long long LL;

void solve() {
  int N;
  LL K;
  cin >> N >> K;

  map <int, vector<pair<int, int> > > drones;    // mapping x + y -> vector of drones {x, y, z, d}
  set<int> active_sum;
  for (int i = 0; i < N; i++) {
    int X, Y, Z;
    string D;
    cin >> X >> Y >> Z >> D;
    if (D == "E") {
      drones[X + Y].push_back({X, 0});
    }
    else {
      drones[X + Y].push_back({X, 1});
    }
    
    active_sum.insert(X + Y);
  }

  LL total_penalty = 0;

  for (auto it = active_sum.begin(); it != active_sum.end(); it++) {
    int sum = *it;
    vector<pair<int, int> > cur = drones[sum];

    sort(cur.begin(), cur.end());

    int can_reach_idx = -1;
    int can_reach_num = 0;
    for (int i = 0; i < int(cur.size()); i++) {
      int cur_x = cur[i].first;
      int cur_dir = cur[i].second;

      while(can_reach_idx != int(cur.size()) - 1 && cur[can_reach_idx + 1].first < cur_x + K) {
        can_reach_idx++;
        if (cur[can_reach_idx].second == 1) {
          can_reach_num++;
        }
      }
      if (cur_dir == 1) {
        can_reach_num = max(0, can_reach_num - 1);
        continue;
      }
      total_penalty += can_reach_num;
    }
  }

  cout << K * N - total_penalty << '\n';



}
int main() {
  int T;
  cin >> T;
  while(T--) {
    solve();
  }
}