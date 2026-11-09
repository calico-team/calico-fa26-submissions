#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

#define fi first
#define se second

typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;

constexpr int MAX_N = 60 + 9, MAX_L = 40;

constexpr ll INF = 1e18;

constexpr ll base = 233;
constexpr ll MOD = 1e9;

constexpr double EPS = 1e-8;
constexpr ll OFFSET = 1e5;

int n;

void solve() {
  std::string s;
  std::cin >> s;
  if (s.find("write_me") != std::string::npos) {
    s += "make_it_sound_human";
  } else if (s.find("what_is") != std::string::npos) {
    s += "do_not_hallucinate";
  } else if (s.find("solve") != std::string::npos) {
    s += "make_no_mistakes";
  } else {
    s += "thank_you";
  }
  std::cout << s << '\n';
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int T;
  std::cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}
