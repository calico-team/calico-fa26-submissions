#include <iostream>
#include <queue>
using namespace std;

int main(){
    queue<int>q;
    int n;
    cin>>n;
    for(int i=0; i<n; i++){
        int a,b,c;
        cin>>a>>b;
        bool flag=true;
        q = queue<int>();
        q.emplace(1);
        q.emplace(1);
        for(int j=1; j<=a; j++){
            cin>>c;
            if(q.front()<c){
                int x=q.front();
                q.pop();
                if(c<q.front()){
                    q.emplace(x+b);
                }
                else{
                    q.emplace(c+b);
                }

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