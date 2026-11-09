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
    std::string S;
    cin>>S;
    bool a=0;
    for(int64_t i=0;i<(int64_t)S.size();i++){
      if(i+8<(int64_t)S.size()&&S.substr(i,8)=="write_me"){
        S+="make_it_sound_human";
        a=1;
      }
      if(i+7<(int64_t)S.size()&&S.substr(i,7)=="what_is"){
        S+="do_not_hallucinate";
        a=1;
      }
      if(i+5<(int64_t)S.size()&&S.substr(i,5)=="solve"){
        S+="make_no_mistakes";
        a=1;
      }
    }
    if(!a){
      S+="thank_you";
    }
    cout<<S<<'\n';
  }
  return 0;
}