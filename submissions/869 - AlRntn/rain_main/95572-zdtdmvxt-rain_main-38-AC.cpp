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
    int64_t N,K;
    cin>>N>>K;
    struct point_t{
      int64_t X,Y,Z,D;
    };
    std::vector<point_t>A(N);
    for(auto &[X,Y,Z,D]:A){
      cin>>X>>Y>>Z;
      char c;cin>>c;
      D=(c=='E'?1:-1);
    }
    int64_t res=2*N*K;
    std::sort(A.begin(),A.end(),[&](point_t a,point_t b)->bool{
      return a.X+a.Y<b.X+b.Y||(a.X+a.Y==b.X+b.Y&&a.X<b.X);
    });
    for(int64_t i=0;i<N;){
      int64_t it=i;
      std::vector<int64_t>vec1,vec2;
      for(;it<N&&A[it].X+A[it].Y==A[i].X+A[i].Y;it++){
        if(A[it].D==1)vec1.push_back(A[it].X);
        else vec2.push_back(A[it].X);
      }
      int64_t j=(int64_t)vec2.size()-1,k=(int64_t)vec2.size()-1;
      for(int64_t i=(int64_t)vec1.size()-1;i>=0;i--){
        while(j>=0&&vec2[j]-vec1[i]>=K){
          j--;
        }
        while(k>=0&&vec2[k]>=vec1[i]){
          k--;
        }
        res-=(j-k);
      }
      j=0,k=0;
      for(int64_t i=0;i<(int64_t)vec2.size();i++){
        while(j<(int64_t)vec1.size()&&vec2[i]-vec1[j]>=K){
          j++;
        }
        while(k<(int64_t)vec1.size()&&vec2[i]>=vec1[k]){
          k++;
        }
        res-=(k-j);
      }
      i=it;
    }
    res/=2;
    cout<<res<<'\n';
  }
  return 0;
}