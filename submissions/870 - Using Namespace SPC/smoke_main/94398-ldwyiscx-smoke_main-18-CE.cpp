// IN THE NAME OF OUR LORD
#include <bits/stdc++.h>
using namespace std; 
#ifndef ONLINE_JUDGE
#include "debug.cpp"
#else
#define debug(...) void(0)
#endif 
int32_t main() { 
  #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout); freopen("error.txt", "w", stderr);
  #endif
  std::ios::sync_with_stdio(false); std::cin.tie(nullptr); 
  int32_t tc = 1; 
  std::cin >> tc; 
  while (tc--) { 
    int64_t n, r; 
    int8_t o = 1; cin >> n >> r; 
    vector<int64_t> a(n); 
    int64_t c = 2, x = 0; 
    for (int64_t i = 0; i < n; i++) cin >> a[i]; 
    for (int64_t i = 0; i < n; i++) { 
      while (c < 2 && x <= a[i]) { 
        c++; if (c < 2) x += r; 
      } if (c == 0) o = 0; 
      else { 
        if (c == 2) x = a[i] + r; 
        c--; 
      } 
    } if ( o ) cout << "YES\n"; else cout << "NO\n" ; 
  } 
} 
/*  */ 