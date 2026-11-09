// IN THE NAME OF OUR LORD
#include <bits/stdc++.h>
using namespace std; 
//#ifndef ONLINE_JUDGE
//#include "debug.cpp"
//#else
//#define debug(...) void(0)
//#endif 
int32_t main() { 
//  #ifndef ONLINE_JUDGE
//    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout); freopen("error.txt", "w", stderr);
//  #endif
  std::ios::sync_with_stdio(false); std::cin.tie(nullptr); 
  int32_t tc = 1; 
  std::cin >> tc; 
  while (tc--) { 
    int64_t n, k; cin >> n >> k; 
    vector<pair<int64_t, int64_t>> v, e; 
    for (int64_t i = 0; i < n; i++) { 
      int64_t x, y, z; char d; 
      cin >> x >> y >> z >> d; 
      if (d == 'E') e.push_back({x + y, x}); 
      else v.push_back({x + y, x}); 
    } std::sort(e.begin(), e.end()); 
    int64_t r = n * k; 
    for (auto &p : v) r -= std::upper_bound(e.begin(), e.end(), pair<int64_t, int64_t>{p.first, p.second}) - std::lower_bound(e.begin(), e.end(), pair<int64_t, int64_t>{p.first, p.second - k + 1 }); ///// 
    cout << r << '\n'; 
  } 
} 
/*  */ 