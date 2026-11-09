#include <iostream>
#include <vector>
using namespace std;

/**
 * Output whether all of the requests can be fulfilled.
 *
 * N: Number of smoke requests
 * R: Number of seconds needed for a smoke charge to recharge
 * A: List of timestamps where smokes are requested
 */
string solve(int N, int R, vector<int> A) {
  long long ready_one = 0;
  long long ready_two = 0;

  for (int i = 0; i < N; ++i) {
    long long t = A[i];
    if (t < ready_one) {
      return "NO";
    }

    long long next_ready = max(t, ready_two) + R;
    ready_one = ready_two;
    ready_two = next_ready;
  }
  return "YES";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while (T--) {
    int N, R;
    cin >> N >> R;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
      cin >> A[i];
    }

    cout << solve(N, R, A) << "\n";
  }
}
