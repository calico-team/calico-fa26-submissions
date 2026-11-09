// IN THE NAME OF OUR LORD
#include <bits/stdc++.h>
using namespace std; 
//#ifndef ONLINE_JUDGE
//#include "debug.cpp"
//#else
//#define debug(...) void(0)
//#endif 
int64_t m; 
vector<int64_t> f; 
int64_t merge(int64_t r, int64_t c) { 
  int64_t b = r * (m + 1), x = b + c, y = x; 
  while (f[x] != x) x = f[x]; while (f[y] != x) { int64_t z = f[y]; f[y] = x; y = z; } 
  return x - b; 
} 
int32_t main() { 
//  #ifndef ONLINE_JUDGE
//    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout); freopen("error.txt", "w", stderr);
//   #endif
  std::ios::sync_with_stdio(false); std::cin.tie(nullptr); 
  int32_t tc = 1; 
  std::cin >> tc; 
  while (tc--) { 
    int64_t n, q; 
    cin >> n >> m >> q; 
    f.resize(n * (m + 1)); iota(f.begin(), f.end(), 0); ///// arpa h 
    vector<int64_t> r(q), c(q), p(q); 
    for (int64_t i = 0; i < q; i++) cin >> r[i] >> c[i] >> p[i]; 
    vector<int64_t> a(n * m); 
    for (int64_t i = q - 1; i >= 0; i--) { 
      int64_t w = p[i]; 
      for (int64_t d = 0; d <= p[i]; d++) { 
        int64_t s = p[i] * p[i] - d * d; 
        while (w * w > s) w--; 
        for (int64_t y = r[i] - d; y <= r[i] + d; y += d + (d == 0)) { 
          for (int64_t x = merge(y, c[i] - w); x <= c[i] + w; x = merge(y, x + 1)) { 
            a[y * m + x] = s - (x - c[i]) * (x - c[i]) + 1; 
            f[y * (m + 1) + x] = y * (m + 1) + x + 1; 
           } 
        }
      } 
    } std::string o; 
    for (int64_t i = 0; i < n; i++) for (int64_t j = 0; j < m; j++) { o += to_string(a[i * m + j]); if (j == m - 1) o += '\n'; else o += ' '; } 
    cout << o; 
  } 
} 
/*  */ 