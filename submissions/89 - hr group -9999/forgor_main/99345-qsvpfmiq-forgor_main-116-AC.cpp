#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string s;
int n;
const int MAXN = 2e5+10;
vector<int> graph[MAXN];
int a[MAXN];

void dfs(int cur, int pre){
    for(int nex : graph[cur]) if(nex != pre){
        a[nex] = cur;
        dfs(nex,cur);
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);

    cin >> s;

    if(s == "FIRST"){
        cin >> n;
        for(int i=1,u,v; i<n; ++i){
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        dfs(1,1);

        for(int i=2; i<=n; ++i) a[1] ^= a[i];
        for(int i=1; i<=n; ++i) cout << a[i] << " \n"[i==n];

    } else {
        cin >> n;
        int bad = 0, x = 0;
        for(int i=1; i<=n; ++i){
            cin >> a[i];
            if(a[i] == -1) bad = i;
            else x ^= a[i];
        }

        if(bad != 1) a[bad] = x;
        for(int i=2; i<=n; ++i) cout << i << " " << a[i] << "\n";
    }
}