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

        if(n==2){
            cout<<0<<' '<<0<<endl; return 0;
        }

        priority_queue<int,vector<int>,greater<int> >qu;
        vector<int>ans; int sum=0;
        for(int q=1;q<=n;q++){
            if(deg[q]==1){
                qu.push(q);
            }
        }

        for(int q=0;q<n-2;q++){
            int apa=qu.top();qu.pop();
            vis[apa]=true;

            int nxt=-1;
            for(auto x : adj[apa]){
                if(!vis[x]){
                    nxt=x; break;
                }
            }

            ans.push_back(nxt); sum+=nxt; 
            deg[nxt]--;

            if(deg[nxt]==1)qu.push(nxt);
        }

        ans.push_back(sum);
        ans.push_back(2*sum);
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
            if(a[q]>0 && q<n-1)sum+=a[q];
        }

        if(n==2){
            cout<<1<<' '<<2<<endl; return 0;
        }

        int hil=0;
        for(int q=1;q<=n;q++){
            if(a[q]==-1)hil=q;
        }

        if(hil<n-1){
            a[hil]=a[n-1]-sum;
        }
        else if(hil==n-1){
            a[hil]=sum;
        }

        for(int q=1;q<=n;q++)deg[q]=1;
        for(int q=1;q<n-1;q++){
            deg[a[q]]++;
        }

        priority_queue<int,vector<int>,greater<int> >qu;
        for(int q=1;q<=n;q++){
            if(deg[q]==1)qu.push(q);
        }

        for(int q=1;q<=n-2;q++){
            int apa=qu.top(); qu.pop();
            cout<<apa<<' '<<a[q]<<endl;

            deg[a[q]]--;
            if(deg[a[q]]==1)qu.push(a[q]);
        }

        int x=qu.top(); qu.pop();
        int b=qu.top(); qu.pop();
        cout<<x<<' '<<b<<endl;
    }
}