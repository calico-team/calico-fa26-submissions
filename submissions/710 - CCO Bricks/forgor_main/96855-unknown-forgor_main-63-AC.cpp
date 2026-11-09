#include "bits/extc++.h"

using namespace std;

constexpr int maxn = 2e5+5;
vector<int>adj[maxn];
int par[maxn];
void dfs(int u, int p){
    par[u]=p;
    for(auto s: adj[u]){
        if(s==p) continue;
        dfs(s,u);
    }
}

void solve1(){
    int n;
    cin>>n;
    for(int i = 0; i<n-1; i++){
        int a,b;
        cin>>a>>b;
        a--,b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0,-1);
    int sum=0;
    for(int i = 1; i<n; i++){
        sum=(sum+par[i])%n;
    }
    cout<<sum<<" ";
    for(int i = 1; i<n; i++){
        cout<<par[i]<<" ";
    }
    cout<<"\n";
}

void solve2(){
    int n;
    cin>>n;
    int arr[n];
    int pos=0;
    for(int i = 0; i<n; i++){
        cin>>arr[i];
        if(arr[i]==-1) pos=i;
    }
    if(pos==0){
        for(int i = 1; i<n; i++){
            cout<<i+1<<" "<<arr[i]+1<<"\n";
        }
    }else{
        int val=arr[0];
        for(int i = 1; i<n; i++){
            if(arr[i]==-1) continue;
            val=(val+n-arr[i])%n;
        }
        arr[pos]=val;
        for(int i = 1; i<n; i++){
            cout<<i+1<<" "<<arr[i]+1<<"\n";
        }
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(ios::failbit);
    string s;
    cin>>s;
    if(s=="FIRST"){
        solve1();
    }else{
        solve2();
    }
}
