#include <iostream>
using namespace std;
int T;
int N;
int R;
long long A[100000];
int RechagrgeState[2];
int Judge(){
    for(int p=0;p<2;p++){
        RechagrgeState[p]=0;
    }
    cin>>N>>R;
    for(int i=1;i<=N;i++){
        cin>>A[i];
    }
    for(int i=1;i<=N;i++){
        bool Flag=false;
        int j=0;
        
        int Gap=A[i]-A[i-1];
        if(RechagrgeState[0]>0){
            if(RechagrgeState[0]<Gap){
                Gap=Gap-RechagrgeState[0];
                RechagrgeState[0]=0;
                if(RechagrgeState[1]>=Gap){
                    RechagrgeState[1] -=Gap;
                }
                if(RechagrgeState[1]<Gap){
                    RechagrgeState[1]=0;
                }
            }
            if(RechagrgeState[0]>=Gap){
                RechagrgeState[0]=RechagrgeState[0]-Gap;
            }
        }

        while (!Flag){
            
            if(RechagrgeState[j] == 0){
                RechagrgeState[j]=R;
                Flag=true;

            }
            j++;
            if(j==2 && !Flag){
                cout<<"NO"<<endl;
                return 1;
            }
        }
    }
    cout<<"YES"<<endl;
    return 0;
}
int main(){
    cin>>T;
    for(int q=0;q<T;q++){
    Judge();
}
}