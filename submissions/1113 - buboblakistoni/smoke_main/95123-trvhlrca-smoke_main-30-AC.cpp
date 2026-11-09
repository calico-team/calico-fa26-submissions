#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;

void solve() {
  int N, R;
  cin >> N >> R;
  priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
  for (int i = 0; i < N; i++) {
    int A;
    cin >> A;
    q.push({A, 1});
  }
  
  int fuses = 2;
  bool active_fusing = false;
  while(!q.empty()) {
    int A = q.top().first;
    int add = q.top().second;
    q.pop();
    if (add == 0) {
      fuses++;
      if (fuses == 1) {
        q.push({A + R, 0});
      }
      else {
        active_fusing = false;
      }
    }
    else {
      fuses--;
      if (fuses < 0) {
        cout << "NO" << '\n';
        return;
      }
      if (!active_fusing) {
        active_fusing = true;
        q.push({A + R, 0});
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