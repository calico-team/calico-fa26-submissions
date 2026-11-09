#include<bits/stdc++.h>
using namespace std;
using std::cout;
#define int long long

int n,m;
vector<vector<int>> linkkk;
int find(int r, int x) {
    if (x!=linkkk[r][x]) linkkk[r][x]=find(r, linkkk[r][x]);
    return linkkk[r][x];
}
void q8() {
    int q; cin>>n>>m>>q;
    bool change=n>m;
    if (!change) linkkk.assign(n, vector<int>(m+1));
    else linkkk.assign(m, vector<int>(n+1));
    vector<int> x(q), y(q), p(q);
    for (int i=q-1; i>=0; i--) cin>>x[i]>>y[i]>>p[i];
    if (!change) {    
        for (int i=0; i<n; i++) {
            for (int j=0; j<=m; j++) linkkk[i][j]=j;
        }
    }else {
        for (int i=0; i<m; i++) {
            for (int j=0; j<=n; j++) linkkk[i][j]=j;
        }
    }
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (int i=0; i<q; i++) {
        if (!change) {
            for (int r=x[i]-p[i]; r<=x[i]+p[i]; r++) {
                int rad=sqrtl(p[i]*p[i]-(r-x[i])*(r-x[i]));
                int c=find(r, y[i]-rad);
                while (c<=y[i]+rad) {
                    ans[r][c]=p[i]*p[i]-(r-x[i])*(r-x[i])-(c-y[i])*(c-y[i])+1;
                    linkkk[r][c]=find(r, c+1);
                    c=find(r, c);
                }
            }
        }else {
            for (int c=y[i]-p[i]; c<=y[i]+p[i]; c++) {
                int rad=sqrtl(p[i]*p[i]-(c-y[i])*(c-y[i]));
                int r=find(c, x[i]-rad);
                while (r<=x[i]+rad) {
                    ans[r][c]=p[i]*p[i]-(c-y[i])*(c-y[i])-(r-x[i])*(r-x[i])+1;
                    linkkk[c][r]=find(c, r+1);
                    r=find(c,r);
                }
            }
        }
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cout<<ans[i][j]<<" ";
        }
        cout<<"\n";
    }
}

signed main() {
    ios::sync_with_stdio(0); 
    cin.tie(0); cout.tie(0);
    int TC=1; cin>>TC;
    while (TC--) q8();
    return 0;
}