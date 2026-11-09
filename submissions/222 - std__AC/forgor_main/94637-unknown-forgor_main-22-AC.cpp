#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
using lli=long long int;
using pii=pair<int, int>;
using plli=pair<lli, lli>;
using vlli=vector<lli>;
using vpii=vector<pii>;
using vplli=vector<plli>;
using vvi=vector<vi>;
using vvlli=vector<vlli>;
using vc=vector<char>;
using vvc=vector<vc>;
using vb=vector<bool>;
using vvb=vector<vector<bool>>;

void dfs(vvi &G, vi &par, int u){
    for (int v : G[u]){
        if (v==par[u]) continue;
        par[v]=u;
        dfs(G, par, v);
    }
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    string t;
    cin >> t;
    if (t=="FIRST"){
        int n;
        cin >> n;
        vvi G(n);
        for (int i=0; i<n-1; ++i){
            int a, b;
            cin >> a >> b;
            --a, --b;
            G[a].push_back(b);
            G[b].push_back(a);
        }
        vi par(n, -1);
        dfs(G, par, 0);
        vi A(n);
        for (int i=1; i<n; ++i) A[i]=par[i];
        int s=0;
        for (int i=1; i<n; ++i) s=(s+par[i])%n;
        A[0]=s;
        for (int i=0; i<n; ++i) cout << A[i] << (i==n-1 ? "" : " ");
        cout << endl;
    }else{
        int n;
        cin >> n;
        vi A(n);
        for (int i=0; i<n; ++i) cin >> A[i];
        vpii E;
        if (A[0]==-1){
            for (int i=1; i<n; ++i) E.push_back({A[i], i});
        }else{
            int ind=-1;
            for (int i=1; i<n; ++i){
                if (A[i]==-1) ind=i;
            }
            // A[0]=A[1]+A[2]...+A[n-1]+A[ind]
            int s=A[0];
            for (int i=1; i<n; ++i){
                if (i!=ind) s=(s-A[i]+n)%n;
            }
            A[ind]=s;
            for (int i=1; i<n; ++i) E.push_back({A[i], i});
        }
        for (pii e : E) cout << e.first+1 << ' ' << e.second+1 << endl;
    }
}