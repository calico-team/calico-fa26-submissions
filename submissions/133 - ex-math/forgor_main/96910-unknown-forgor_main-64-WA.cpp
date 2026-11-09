#include<bits/stdc++.h>
using namespace std;
#define int long long 
#pragma GCC optimize("O3,unroll-loops")

const int maxn=2e5;
vector<int>adj[maxn+2];
int deg[maxn+2];
bool vis[maxn+2];

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    string s; cin>>s;
    if(s=="FIRST"){
        int n; cin>>n;
        for(int q=1;q<n;q++){
            int u,v; cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
            deg[u]++,deg[v]++;
        }

        queue<int>qu;
        vector<int>ans; int sum=0;
        for(int q=1;q<=n;q++){
            if(deg[q]==1){
                qu.push(q); vis[q]=true;
            }
        }

        int ke=0;
        while(qu.size()){
            int apa=qu.front();qu.pop();
            bool ada=false;
            ke=apa;

            for(auto x : adj[apa]){
                deg[x]--;
                if(deg[x]==1){
                    ans.push_back(x); sum+=x;
                    qu.push(x);
                    vis[x]=true;
                    ada=true;
                }
            }

        }
        ans.push_back(ke); sum+=ke;


        ans.push_back(sum);
        for(auto x : ans){
            cout<<x<<' ';
        }
        cout<<endl;
    }
    else{
        int n; cin>>n;
        int a[n+1];
        int sum=0;

        for(int q=1;q<=n;q++){
            cin>>a[q];
            if(a[q]>0 && q<n)sum+=a[q];
        }

        for(int q=1;q<=n;q++){
            if(a[q]==-1){
                a[q]=a[n]-sum;
            }
        }

        for(int q=1;q<n;q++){
            deg[a[q]]++;
        }

        queue<int>qu;
        for(int q=1;q<=n;q++){
            if(!deg[q])qu.push(q);
        }

        vector<int>ord;
        int ke=0;

        while(qu.size()){
            int apa=qu.front(); qu.pop();
            ord.push_back(apa); ke++;
            if(ke==n)break;

            deg[a[ke]]--;
            if(deg[a[ke]]==0)qu.push(a[ke]);
        }

        for(int q=0;q<n-1;q++){
            cout<<ord[q]<<' '<<a[q+1]<<endl;
        }
    }
}