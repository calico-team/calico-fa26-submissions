#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+5;
int fa[N];
vector<int> e[N];
void dfs(int x, int ff){
    fa[x]=ff;
    for(auto y:e[x]){
        if(y==ff) continue;
        dfs(y, x);
    }
}
int main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    string O;
    cin >> O;
    if(O=="FIRST"){
        int n;
        cin >> n;
        for(int i=1; i<n; ++i){
            int x, y;
            cin >> x >> y;
            e[x].push_back(y);
            e[y].push_back(x);
        }
        dfs(1,0);
        int v=0;
        for(int i=2; i<=n; ++i){
            v^=fa[i];
        }
        fa[1]=v;
        for(int i=1; i<=n; ++i){
            cout << fa[i] << " \n"[i==n];
        }
    }else{
        int n;
        cin >> n;
        for(int i=1; i<=n; ++i){
            cin >> fa[i];
        }
        if(fa[1]!=-1){
            int v=0, p=0;
            for(int i=1; i<=n; ++i){
                if(fa[i]==-1) p=i;
                else v^=fa[i];
            }
            fa[p]=v;
        }
        for(int i=2; i<=n; ++i){
            cout << fa[i] << ' ' << i << '\n';
        }
    }
    return 0;
}