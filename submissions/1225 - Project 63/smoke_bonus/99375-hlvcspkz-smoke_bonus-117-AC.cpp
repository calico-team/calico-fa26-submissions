#include <iostream>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int input;
    cin>>input;
    for(int i = 0; i < input; i++) {
      int N,R;
      cin>>N>>R;
      int nums[N] = {};
      for(int j = 0; j < N; j++) 
        cin>>nums[j];
      
      bool works = true;
      int smoke1 =0;
      int smoke2 =0;
      
      for(int k = 0; k < N; k++){  
        if(nums[k] >= smoke1)
          smoke1 = nums[k] + R;
        else if(nums[k] >= smoke2){
          if(smoke1 > smoke2) smoke2 = smoke1 + R;
        	else smoke2 = smoke2 + R;
        }
        else {
          works = false;
          break;
        }
      }
      
      if(!works) cout<<("NO\n");
      else cout<<("YES\n");
    }
}
















