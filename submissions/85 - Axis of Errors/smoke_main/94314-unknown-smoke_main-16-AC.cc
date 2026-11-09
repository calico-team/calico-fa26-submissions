#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
#include <stack>

using namespace std;

typedef long long ll;

void get_vector(int n, vector<long long>& v) {
  for (int i = 0; i < n; i++) {
    int d;
    cin >> d;
    v.push_back(d);
  }
}

string solve(int N, int R, vector<ll>& A) {
  int r1 = 0, r2 = 0;
  for (int n : A) {
    //cout << r1  << " , " << r2 << endl;
  	if (r1 <= n) {
        r1 = max(n + R, r2 + R);
    } else {
        return "NO";
    }
    if (r2 < r1) swap(r1, r2);
  }
  return "YES";
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) {
    int N, R;
    cin >> N >> R;
    vector<long long> A;
    get_vector(N, A);
    cout << solve(N, R, A) << endl;
  }
}
