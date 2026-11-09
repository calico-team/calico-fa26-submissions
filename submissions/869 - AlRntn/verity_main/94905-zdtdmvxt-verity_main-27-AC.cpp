#include "bits/stdc++.h"
#ifdef AlRntn
#include "debug.hpp"
#else
#define debug(...) void(0)
#define tstr(...) void(0)
#endif
void interact(){
  std::cout << std::endl;
  std::cout.flush();
}
int main(){
#ifdef AlRntn
//freopen("inputf.in" , "r" , stdin); freopen("outputf.out" , "w" , stdout); freopen("errorf.out" , "w" , stderr);
#endif
  using namespace std;
  ios_base::sync_with_stdio(false), cin.tie(nullptr);
  int32_t tc;
  std::cin >> tc;
  while(tc--){
    [&](){
      int64_t N,K;
      cin>>N>>K;
      std::vector<char>A(K);
      for(int64_t i=0;i<K;i++)cin>>A[i];
      std::string S(N,'_');
      for(int64_t i=0;i<K;i++){
        std::string ss;
        for(int64_t j=0;j<N;j++)ss.push_back(A[i]);
        cout<<ss;
        interact();
        std::string res;
        cin>>res;
        if(res=="CORRECT")return;
        for(int64_t i=0;i<N;i++){
          if(res[i]!='_')S[i]=res[i];
        }
      }
      cout<<S;
      interact();
      std::string res;
      cin>>res;
      assert(res=="CORRECT");
    }();
  }
  return 0;
}