#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;

void solve() {
  int N, R;
  cin >> N >> R;
  priority_queue<pair<int, bool>, vector<pair<int, bool> >, greater<pair<int, bool> > > q;
  for (int i = 0; i < N; i++) {
    int A;
    cin >> A;
    q.push({A, false});
  }
  
  int fuses = 2;
  bool first_fuse_done = true;
  while(!q.empty()) {
    int A = q.top().first;
    bool add = q.top().second;
    q.pop();
    if (add) {
      fuses++;
      if (fuses == 1) {
        q.push({A + R, true});
      }
      else {
        first_fuse_done = true;
      }
    }



    if (!add) {
      fuses--;
      if (fuses < 0) {
        cout << "NO" << '\n';
        return;
      }
      if (first_fuse_done) {
        first_fuse_done = false;
        q.push({A + R, true});
      }
    }
  }
  cout <<  "YES" << '\n';
}

int main() {
  fastio;
  int T;
  cin >> T;
  while(T--) {
    solve();
  }
}