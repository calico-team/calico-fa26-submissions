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
    int64_t n, k; 
    cin >> n >> k;  
    vector<char> a(k); 
    for (int64_t i = 0; i < k; i++) cin >> a[i]; 
    string s(n, '?'); 
    for (int64_t j = 0; ; j++) { 
      string g = s; 
      for (auto &c : g) if (c == '?') c = a[j]; 
      cout << g << endl; ///// 
      string r; cin >> r; 
      if (r == "CORRECT") break; 
      for (int64_t i = 0; i < n; i++) if (r[i] != '_') s[i] = r[i]; 
    } 
  } 
} 
/*  */ 