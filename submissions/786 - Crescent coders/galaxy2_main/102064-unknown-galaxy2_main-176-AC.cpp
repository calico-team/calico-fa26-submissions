#include <bits/stdc++.h>
using namespace std;
struct Query {int a,b,sc,ec,k;bool normal;};
struct Solver {
 int n,m,q,V,stamp=0;
 vector<string> grid;
 vector<vector<int>> adj, midSources;
 vector<int> column,seen,dist;
 vector<Query> queries;
 vector<char> good;
 void addEdge(int a,int b){adj[a].push_back(b);adj[b].push_back(a);}
 void build(){
  V=2*n*m;adj.resize(V);column.resize(V);midSources.resize(m);seen.assign(V,0);dist.resize(V);
  for(int r=0;r<n;r++) for(int c=0;c<m;c++){
   char t=grid[r][c];int x=2*(r*m+c);
   column[x]=column[x+1]=c;
   if(t!='R')midSources[c].push_back(x);
   if(t!='B')midSources[c].push_back(x+1);
   if(t=='.')addEdge(x,x+1);
   if(c+1<m){char o=grid[r][c+1];
    if(t!='R'&&o!='R')addEdge(x,x+2);
    if(t!='B'&&o!='B')addEdge(x+1,x+3);
   }
   if(r+1<n){char o=grid[r+1][c];
    if(t!='R'&&o!='R')addEdge(x,x+2*m);
    if(t!='B'&&o!='B')addEdge(x+1,x+2*m+1);
   }
  }
 }
 void divide(int l,int r, vector<int> &ids){
  if(ids.empty())return;
  int mid=(l+r)/2;
  vector<int> bfs(V);
  for(int source:midSources[mid]){
   ++stamp;
   int head=0,tail=0;
   bfs[tail++]=source;
   seen[source]=stamp;dist[source]=0;
   while(head<tail){
    int u=bfs[head++];int nd=dist[u]+1;
    for(int v:adj[u]){
     if(seen[v]!=stamp&&column[v]>=l&&column[v]<=r){
      seen[v]=stamp;dist[v]=nd;bfs[tail++]=v;
     }
    }
   }
   int write=0;
   for(int qi:ids){
    const Query &z=queries[qi];
    bool reachable=false;
    if(seen[z.a]==stamp){
     int d=dist[z.a];
     if(seen[z.b]==stamp&&d+dist[z.b]<=z.k)reachable=true;
     if(z.normal&&seen[z.b+1]==stamp&&d+dist[z.b+1]<=z.k)reachable=true;
    }
    if(reachable)good[qi]=true;
    else ids[write++]=qi;
   }
   ids.resize(write);
   if(ids.empty())return;
  }
  if(l==r)return;
  vector<int> left,right;
  left.reserve(ids.size());right.reserve(ids.size());
  for(int qi:ids){
   const Query &z=queries[qi];
   if(z.sc<mid&&z.ec<mid)left.push_back(qi);
   if(z.sc>mid&&z.ec>mid)right.push_back(qi);
  }
  divide(l,mid-1,left);
  divide(mid+1,r,right);
 }
 void run(){
  cin>>n>>m>>q;
  grid.resize(n);for(auto &s:grid)cin>>s;
  build();queries.resize(q);good.assign(q,false);
  for(auto &z:queries){
   int sr,sc,er,ec;cin>>sr>>sc>>er>>ec>>z.k;
   z.sc=sc;z.ec=ec;z.a=2*(sr*m+sc);
   char t=grid[er][ec];z.b=2*(er*m+ec)+(t=='R');z.normal=(t=='.');
  }
  vector<int> ids(q);iota(ids.begin(),ids.end(),0);
  divide(0,m-1,ids);
  for(char x:good)cout<<(x?"YES":"NO")<<'\n';
 }
};
int main(){ios::sync_with_stdio(false);cin.tie(nullptr);int T;cin>>T;while(T--){Solver s;s.run();}}
