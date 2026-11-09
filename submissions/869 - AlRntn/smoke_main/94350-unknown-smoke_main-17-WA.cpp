#include "bits/stdc++.h"
#ifdef AlRntn
#include "debug.hpp"
#else
#define debug(...) void(0)
#define tstr(...) void(0)
#endif
int main(){
#ifdef AlRntn
freopen("inputf.in" , "r" , stdin); freopen("outputf.out" , "w" , stdout); freopen("errorf.out" , "w" , stderr);
#endif
  using namespace std;
  ios_base::sync_with_stdio(false), cin.tie(nullptr);
  int32_t tc;
  std::cin >> tc;
  while(tc--){
    int64_t N,R;
    cin>>N>>R;
    std::vector<int64_t>A(N);
    for(auto &a:A)cin>>a;
    int64_t cnt=0;
    std::array<int64_t,2>nxt={-(int64_t)1e18,-(int64_t)1e18};
    [&](){
      nxt[0]=nxt[1]=0;
      for(int64_t i=0;i<N;i++){
        if(nxt[1]>A[i]){
          cout<<"NO\n";
          return;
        }
        if(nxt[1]<=A[i]){
          nxt[1]=A[i]+R;
        }else if(nxt[0]<=A[i]){
          nxt[0]=nxt[1]+R;
          std::swap(nxt[0],nxt[1]);
        }
      }
      cout<<"YES\n";
    }();
  }
  return 0;
}