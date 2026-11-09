#include<bits/stdc++.h>
#include <cassert>
using namespace std;
#define printf if(false)
int main(){
    cin.tie(nullptr);
    cin.sync_with_stdio(false);

    string phase;cin>>phase;

    if(phase=="FIRST"){
        unsigned n;cin>>n;
        vector<vector<unsigned>>adj(n+1);
        for(unsigned i=1;i<n;++i){
            unsigned u,v;cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<unsigned>ans(n+1);
        auto dfs=[&](auto&& self,unsigned node,unsigned parent)->void{
            printf("dfs node=%d, parent=%d\n",node,parent);
            ans[node]=(parent<<1U);
            ans[node]+=adj[node].size()%2==1;
;
printf("ansnode=%d+%d=%d\n",parent<<1U,adj[node].size()%2==1,ans[node]);
            for(unsigned i:adj[node]){
                if(i==parent)continue;
                self(self,i,node);
            }
        };
        dfs(dfs,1,0);
        for(unsigned i=1;i<=n;++i){
            cout<<ans[i]<<' ';
        }
        cout<<endl;
        return 0;
    }else{
        unsigned n;cin>>n;
        vector<unsigned>parent(n+1);
        vector<unsigned>degpar(n+1);
        vector<unsigned>deg(n+1,0);
        for(unsigned i=1;i<=n;++i){
            int a_;cin>>a_;
                degpar[i]=1e9;
            if(a_!=-1){
                unsigned a=a_;
                degpar[i]=a%2;
                a>>=1;
                if(a!=0){
                deg[i]++;
                deg[a]++;
                }
                parent[i]=a;
            }else{
                parent[i]=1e9;
            }
        }

        for(int i=1;i<=n;++i){
            printf("%d: par=%d, degi=%d, degpar=%s\n",i,parent[i],deg[i],degpar[i]?"odd":"EVEN");
        }

        vector<unsigned>wrong;
        for(unsigned i=1;i<=n;++i){
            if(degpar[i]==1e9||deg[i]%2!=degpar[i]%2){
                wrong.push_back(i);
                printf("wrongpb %d\n",i);
            }
        }
        assert(wrong.size()<=2);
        if(wrong.size()==1){
        }else{
        cout<<wrong[0]<<' '<<wrong[1]<<endl;
        }
        for(unsigned i=1;i<=n;++i){
            if(parent[i]==1e9||parent[i]==0)continue;
            cout<<i<<' '<<parent[i]<<endl;
        }
        return 0;

    }
}
