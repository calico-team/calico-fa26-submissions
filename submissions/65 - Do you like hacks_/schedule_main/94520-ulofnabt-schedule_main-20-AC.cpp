#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+5;
int fa[N], dep[N];
vector<int> e[N];
void dfs(int x){
    for(auto y:e[x]){
        dep[y]=dep[x]+1;
        dfs(y);
    }
}
int main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while(T--){
        int n, m, k;
        cin >> n >> m >> k;
        for(int i=0; i<=n; ++i){
            e[i].clear();
        }
        for(int i=1; i<=n; ++i){
            cin >> fa[i];
            e[fa[i]].push_back(i);
        }
        dep[0]=0;
        dfs(0);
        map<int,int> mp;
        for(int i=1; i<=n; ++i){
            mp[dep[i]]++;
        }
        int ans=0, pre=0;
        for(int i=1; i<=m; ++i){
            int x=mp[i];
            if(x>=k){
                ans+=k, pre+=x-k;
            }else if(x+pre>=k){
                ans+=k, pre-=k-x;
            }else{
                ans+=x+pre, pre=0;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}