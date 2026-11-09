#include<bits/stdc++.h>
using namespace std;
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        int n; long long r;
        scanf("%d %lld",&n,&r);
        long long r1=0,r2=0;  
        bool ok=1;
        for(int i=0;i<n;i++){
            long long t; scanf("%lld",&t);
            if(!ok)continue;          
            if(t>=r1){                 
                r1=max(t,r2)+r;
            }else if(t>=r2){          
                r2=max(t,r1)+r;
            }else{
                ok=0;
            }
        }
        if(ok==true){
			cout<<"YES"<<endl;		
		}    
		else{
			cout<<"NO"<<endl;
		}
		}
    return 0;
}