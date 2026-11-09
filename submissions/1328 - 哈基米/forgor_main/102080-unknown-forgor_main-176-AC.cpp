#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string phase; cin >> phase;
    int N; cin >> N;
    if(phase=="FIRST"){
        vector<vector<int>>adj(N+1);
        for(int i=0;i<N-1;i++){ 
			int u,v;cin>>u>>v; adj[u].push_back(v); adj[v].push_back(u);
		}
        vector<int>parent(N+1,0);
        vector<int>order; order.push_back(1); parent[1]=0;
        for(int i=0;i<(int)order.size();i++){ int u=order[i]; for(int v:adj[u]) if(v!=parent[u]){ parent[v]=u; order.push_back(v); } }
        int xr = 0;
        for(int i=2;i<=N;i++)xr^=parent[i];
        cout << xr;
        for(int i=2;i<=N;i++)cout<<" "<<parent[i];
        cout<<"\n";
    }else{
        vector<int>A(N+1);
        for(int i=1;i<=N;i++)cin>>A[i];
        int k=-1;
        for(int i=1;i<=N;i++)if(A[i]==-1){
			k=i;
			break;
		}
        vector<int>parent(N+1,0);
        if(k==1){
            for(int i=2;i<=N;i++)parent[i]=A[i];
        } else {
            int xr = A[1];
            for(int i=2;i<=N;i++)if(i!=k)xr^=A[i];
            parent[k] = xr;
            for(int i=2;i<=N;i++)if(i!=k)parent[i]=A[i];
        }
        for(int i=2;i<=N;i++)cout<<i<<" "<<parent[i]<<"\n";
    }
    return 0;
}
