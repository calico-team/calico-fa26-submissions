#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int long long
#define pb push_back
#define mp make_pair
#define endl '\n'
#define f first
#define s second 
#define INF 0x3f3f3f3f
#define fileio(file) freopen(file ".in", "r", stdin); freopen(file ".out", "w", stdout)
#define pout(v); for (auto i : v) {cout << i << " ";} cout << endl;
#define FOR(i, n, m) for (int i = (n); i < (m); i++)
#define ROF(i, n, m) for (int i = (n); i > (m); i--)

int Q;

void solve() {
  int N, R;
  cin >> N >> R;

  int A, trchg = INF, ok = 1, curr = 2;
  FOR(i, 0, N) {
    cin >> A;
    if (ok) {
      // can rchg
      while(curr < 2 && trchg <= A) {
        curr++;
        trchg = (curr == 2) ? trchg + R : INF;
      } 
      // cooked
      if (!curr) { ok = 0; continue; }

      if (curr == 2) trchg = A + R;
      curr--;
    } 
  }

  cout << (ok ? "YES" : "NO") << endl;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);

  cin >> Q;

  while(Q--) solve();

  return 0;
}
