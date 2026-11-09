// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin>>t;
    while(t--){
        int n,m,k;
        cin>>n>>m>>k;
        vector<int>v;
        vector<int>dis(n,INT_MAX);
        queue<int>q;
        map<int,vector<int>>rg;
        for(int x=0;x<n;x++){
            int a;
            cin>>a;
            a-=1;
            v.push_back(a);
            if(a==-1){
                dis[x]=0;
                q.push(x);
            }
            if(rg.count(a)){
                rg[a].push_back(x);
            }
            else{
                rg[a]={x};
            }
        }
        while(!q.empty()){
            int f=q.front();
            q.pop();
            if(rg.count(f)){
                for(const int &i: rg[f]){
                    if(dis[i]>dis[f]+1){
                        dis[i]=dis[f]+1;
                        q.push(i);
                    }
                }
            }
        }
        map<int,int>mp;
        int md=0;
        for(int x=0;x<n;x++){
            if(md<dis[x]){
                md=dis[x];
            }
            if(mp.count(dis[x])){
                mp[dis[x]]++;
            }
            else{
                mp[dis[x]]=1;
            }
        }
        int tot=0;
        int ci=0;
        int tm=0;
        while(m--){
            int temp=k;
            if(ci<=md){
                if(k<=mp[ci]){
                    mp[ci]-=k;
                    if(mp[ci]==0){
                        ci++;
                    }
                    tot+=k;
                }
                else{
                    //cout<<'f';
                    while(ci<=tm&&ci<=md&&k>mp[ci]){
                        tot+=mp[ci];
                        k-=mp[ci];
                        ci++;
                    }
                    if(ci<=md&&ci<=tm){
                        
                        mp[ci]-=k;
                        if(mp[ci]==0){
                            ci++;
                        }
                        tot+=k;
                    }
                }
            }
            k=temp;
            //cout<<tot<<'a'<<ci<<' ';
            tm++;
        }
        cout<<tot;
        if(t!=0){
            cout<<endl;
        }
    }
}
