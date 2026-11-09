#include <bits/stdc++.h>
using namespace std;

void normtree(int pos,vector<vector<int>> &connections,vector<int> &parent){
    for(int i=0;i<connections[pos].size();i++){
        if(connections[pos][i]!=parent[pos]){
            parent[connections[pos][i]]=pos;
            normtree(connections[pos][i],connections,parent);
        }
    }
}

void first(){
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    int inp1,inp2;
    for(int i=1;i<n;i++){
        cin >> inp1 >> inp2;
        inp1--;
        inp2--;
        adj[inp1].push_back(inp2);
        adj[inp2].push_back(inp1);
    }
    vector<int> parent(n,-1);
    normtree(0,adj,parent);
    parent[0]=0;
    for(int i=1;i<n;i++) parent[0]^=parent[i];
    for(int i:parent) cout << i << ' ';
    cout << '\n';
}

void second(){
    int n;
    cin >> n;
    vector<int> parent(n);
    for(int i=0;i<n;i++) cin >> parent[i];
    int cxor=0;
    for(int i=0;i<n;i++) if(parent[i]!=-1) cxor^=parent[i];
    for(int i=0;i<n;i++) if(parent[i]==-1) parent[i]=cxor;
    for(int i=1;i<n;i++) cout << i+1 << ' ' << parent[i]+1 << '\n';
}




void solve(){
    string inp;
    cin >> inp;
    if(inp=="FIRST"){
        first();
    }
    else {
        second();
    }
}


int main(){
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tc=1;
  //cin >> tc;
  for (int t=1;t<=tc;t++){
    solve();
  }
}