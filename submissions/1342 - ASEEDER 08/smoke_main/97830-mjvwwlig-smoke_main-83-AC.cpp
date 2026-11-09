#include<bits/stdc++.h>
using namespace std;

int main(){
    int T;
    cin>>T;
    while(T--){
        int n;
        long long r;                 
        cin>>n>>r;
        long long a[100005];
        for(int j=0;j<n;j++) cin>>a[j];

        queue<long long> q;          
        int flag=0;              

        for(int j=0;j<n;j++){

            while(!q.empty() && q.front()<=a[j]) q.pop();

          
            if((int)q.size()<2){
                long long st = q.empty() ? a[j] : q.back();
                q.push(st+r);        
            } else {
                flag=1;              
                break;
            }
        }
        if(flag==0) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}
