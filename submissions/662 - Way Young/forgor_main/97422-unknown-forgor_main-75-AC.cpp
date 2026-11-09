#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin>>s;
    if(s=="FIRST"){
        int n;
        cin>>n;
        vector<vector<int>> a(n);
        for(int i=1;i<n;i++){
            int x,y;
            cin>>x>>y;
            x--;
            y--;
            a[x].push_back(y);
            a[y].push_back(x);
        }
        queue<int> q;
        q.push(0);
        vector<int> d(n);
        d[0]=-1;
        int xr=0;
        while(q.size()){
            int i=q.front();
            q.pop();
            for(int j:a[i]){
                if(j==d[i]){
                    continue;
                }
                d[j]=i;
                xr^=i+1;
                q.push(j);
            }
        }
        d[0]=xr;
        for(int i=0;i<n;i++){
            if(!i){
                cout<<xr;
            }
            else{
                cout<<' '<<d[i]+1;
            }
        }
    }
    else{
        int n;
        cin>>n;
        vector<int> a(n);
        for(int& x:a){
            cin>>x;
        }
        if(a[0]==-1){
            for(int i=1;i<n;i++){
                cout<<i+1<<' '<<a[i]<<"\n";
            }
        }
        else{
            int k;
            for(int i=1;i<n;i++){
                if(a[i]==-1){
                    k=i;
                    continue;
                }
                a[0]^=a[i];
            }
            a[k]=a[0];
            for(int i=1;i<n;i++){
                cout<<i+1<<' '<<a[i]<<"\n";
            }
        }
    }
    return 0;
}