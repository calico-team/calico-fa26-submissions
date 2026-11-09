#include <iostream>
#include <algorithm>

using namespace std;

int main(){
   
    long long n;
   
    cin>>n;
    for(long long i=0; i<n; i++){
        long long x=0;
        long long y=0;
        long long a,b,c;
        cin>>a>>b;
        bool flag=true;
    
        for(long long j=1; j<=a; j++){
            cin>>c;
            
            
            if(x<=c&& flag){
    
                x=y;

                y=max(c,y)+b;
            }
            else{
                flag=false;
                
                
            } 
           
        
        }

        if(flag){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
        

}
}