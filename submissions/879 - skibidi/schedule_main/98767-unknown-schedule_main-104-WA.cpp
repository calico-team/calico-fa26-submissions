#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> ch[10000];
int dep[10000];

void dfs(int x){
    dep[x]=1;
    for (int i:ch[x]){
        dfs(i);
        dep[x]=max(dep[x],dep[i]+1);
    }
}

signed main(){
    int t;
    cin>>t;
    for (int tt=0; tt<t; tt++){
        int n,m,k;
        cin>>n>>m>>k;
        vector<int> aa;
        int ans=0;
        for (int i=0; i<n; i++){
            ch[i]={};
        }
        for (int i=0; i<n; i++){
            int x;
            cin>>x;
            if (x==0) aa.push_back(x);
            else ch[x-1].push_back(i);
        }
        //how the fuck do you prove this works (its probably wrong)
        for (int i:aa) dfs(i);
        priority_queue<pair<int,int>> pq;
        for (int i:aa){
            pq.push({dep[i],i});
        }
        for (int i=0; i<m; i++){
            vector<pair<int,int>> v;
            for (int i=0; i<k; i++){
                if (pq.empty()) break;
                pair<int,int> p=pq.top();
                pq.pop();
                for (int i:ch[p.second]){
                    v.push_back({dep[i],i});
                }
                ans++;
            }
            for (pair<int,int> p:v) pq.push(p);
        }
        cout<<ans<<endl;
    }
}