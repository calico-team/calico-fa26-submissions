#include<iostream>
#include<vector>
#include<string>
using namespace std;

vector<int>solve_phase1(int N,vector<pair<int,int>>&E){
    vector<vector<int>>g(N+1);
    for(auto&e:E){
        g[e.first].push_back(e.second);
        g[e.second].push_back(e.first);
    }
    vector<int>p(N+1,0),q={1};
    vector<bool>vis(N+1,false);
    vis[1]=true;
    for(int i=0;i<(int)q.size();i++){
        int u=q[i];
        for(int v:g[u])if(!vis[v]){
            vis[v]=true;
            p[v]=u;
            q.push_back(v);
        }
    }
    vector<int>A(N);
    int x=0;
    for(int v=2;v<=N;v++){
        A[v-1]=p[v];
        x^=p[v];
    }
    A[0]=x;
    return A;
}

vector<pair<int,int>>solve_phase2(int N,vector<int>&A){
    int k=-1;
    for(int i=0;i<N;i++)if(A[i]==-1)k=i;
    if(k!=0){
        int x=A[0];
        for(int i=1;i<N;i++)if(i!=k)x^=A[i];
        A[k]=x;
    }
    vector<pair<int,int>>res;
    for(int v=2;v<=N;v++)res.push_back({v,A[v-1]});
    return res;
}

int main(){
    string phase;
    cin>>phase;
    int N;
    cin>>N;

    if(phase=="FIRST"){
        vector<pair<int,int>>E(N-1);
        for(int i=0;i<N-1;i++){
            cin>>E[i].first>>E[i].second;
        }
        vector<int>A=solve_phase1(N,E);
        for(int i=0;i<N;i++){
            if(i>0)cout<<' ';
            cout<<A[i];
        }
        cout<<'\n';
    }else{
        vector<int>A(N);
        for(int i=0;i<N;i++){
            cin>>A[i];
        }
        vector<pair<int,int>>edges=solve_phase2(N,A);
        for(auto&e:edges){
            cout<<e.first<<' '<<e.second<<'\n';
        }
    }
}