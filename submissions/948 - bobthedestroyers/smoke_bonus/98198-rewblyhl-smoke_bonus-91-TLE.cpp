#include <iostream>

using namespace std;

int main(){
   
    int n;
   
    cin>>n;
    for(int i=0; i<n; i++){
        int x=0;
        int y=0;
        int a,b,c;
        cin>>a>>b;
        bool flag=true;
    
        for(int j=1; j<=a; j++){
            cin>>c;
            int p;
            
            if(x<=c&& flag){
    
                if(c<y){
                    p=y+b;
                }
                else{
                    p=c+b;
                }
                 x=y;
                 y=p;   

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