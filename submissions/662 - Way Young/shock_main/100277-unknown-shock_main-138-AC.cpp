#include <bits/stdc++.h>
using namespace std;

#define int long long
#define fu(i,a,b) for(int i=(a);i<=(b);i++)
#define fd(i,a,b) for(int i=(a);i>=(b);i--)
#define V vector 
#define sz(x) (int)(x).size()

struct DSU {
    V<int> p;
    DSU(int n){
        p.resize(n);
        fu(i,0,n-1) {p[i]=i;}
    }
    int find(int x) {
        if(p[x]==x) return x;
        else return p[x]=find(p[x]);
    }
    void merge(int x,int y) {
        x=find(x),y=find(y);
        p[x]=y;
    }
};

void solve() {
    int n,m,q;
    cin>>n>>m>>q;
    
    V<V<int>> ans(n, V<int>(m,0));

    V<array<int,3>> queries(q);
    fu(i,0,q-1) {
        cin>>queries[i][0]>>queries[i][1]>>queries[i][2];
    }
    V<DSU> dsu;
    if(n < m) {
        fu(i,0,n-1) {
            dsu.push_back(DSU(m+1));
        }
     } else {
        fu(i,0,m-1) {
            dsu.push_back(DSU(n+1));
        }
    }
    fd(i,q-1,0) {
        int P=queries[i][2], X=queries[i][0], Y=queries[i][1];
        if(n < m) {
            fu(row, max(0ll, queries[i][0]-P),min(n-1,
            queries[i][0] + P)) {
                int le=max(0ll, Y-(int)sqrt(P*P - (X-row)*(X-row))), 
                re=min(m-1, Y+(int)sqrt(P*P - (X-row)*(X-row)));

                for(int j=dsu[row].find(le); j<=re; j=dsu[row].find(j)) {
                    if(j>re) break;
                    ans[row][j]=P*P-((X-row)*(X-row) + (Y-j)*(Y-j))+1;
                    dsu[row].merge(j, j+1); // now the find should be different
                }
            }
        } else {
            fu(col, max(0ll, Y-P), min(m-1,Y+P)) {
                int le=max(0ll, X-(int)sqrt(P*P - (Y-col)*(Y-col))), 
                re=min(n-1,X+(int)sqrt(P*P - (Y-col)*(Y-col)));
                for(int j=dsu[col].find(le); j<=re; j=dsu[col].find(j)) {
                    if(j>re) break;
                    ans[j][col]=P*P-((X-j)*(X-j) + (Y-col)*(Y-col))+1;
                    dsu[col].merge(j, j+1);
                }
            }
        }
    }

    fu(i,0,n-1){fu(j,0,m-1) {
        if(ans[i][j]==-1)cout<<"0 ";
        else cout<<ans[i][j]<<" ";
    }cout<<'\n';
}
}

signed main() {
    int t;
    cin>>t;
    while(t--) {
        solve();
    }
}