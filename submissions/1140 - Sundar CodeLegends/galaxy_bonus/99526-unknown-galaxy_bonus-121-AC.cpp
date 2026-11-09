#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e6 + 5;
const int LOG = 17, MAXB = 1<<LOG;
const int MOD = 998244353;
const int mod = 1e9 + 7;
const int K = 5e3+5;
vector<int> parent(N);
vector<int> siz(N);
void setup(int n){
    for(int i = 0 ; i <= n ; i++)parent[i] = i, siz[i] = 1;
}
int find_(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_(parent[v]);
}
void merge(int a, int b) {
    a = find_(a);
    b = find_(b);
    if (a != b) {
        if (siz[a] < siz[b])
            swap(a, b);
        parent[b] = a;
        siz[a] += siz[b];
    }
}
int convert(int i, int j,int mode, int m){
    int p = i * m + j;
    p *= 2;p += mode;
    return p;
}
void solve(){
    int n,m,q;cin >> n >> m >> q;
    vector<string> a(n);
    for(int i = 0 ; i < n ; i ++)cin >> a[i];
    setup(n * m * 2 + 5);
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < m ; j ++){
            if(a[i][j] == 'R'){
                if(i-1 >= 0 and a[i-1][j] != 'B'){
                    int u = convert(i, j, 0, m);
                    int v = convert(i-1, j, 0, m);
                    merge(u,v);
                }
                if(j-1 >= 0 and a[i][j-1] != 'B'){
                    int u = convert(i, j, 0, m);
                    int v = convert(i, j - 1, 0, m);
                    merge(u,v);
                }
                if(i+1<n and a[i+1][j] != 'B'){
                    int u = convert(i, j, 0, m);
                    int v = convert(i+1, j, 0, m);
                    merge(u,v);
                }
                if(j+1<m and a[i][j+1] != 'B'){
                    int u = convert(i, j, 0, m);
                    int v = convert(i,j+1, 0, m);
                    merge(u,v);
                }
            }
            else if(a[i][j] == 'B'){
                if(i-1 >= 0 and a[i-1][j] != 'R'){
                    int u = convert(i, j, 1, m);
                    int v = convert(i-1, j, 1, m);
                    merge(u,v);
                }
                if(j-1 >= 0 and a[i][j-1] != 'R'){
                    int u = convert(i, j, 1, m);
                    int v = convert(i, j - 1, 1, m);
                    merge(u,v);
                }
                if(i+1<n and a[i+1][j] != 'R'){
                    int u = convert(i, j, 1, m);
                    int v = convert(i+1, j, 1, m);
                    merge(u,v);
                }
                if(j+1<m and a[i][j+1] != 'R'){
                    int u = convert(i, j, 1, m);
                    int v = convert(i,j+1, 1, m);
                    merge(u,v);
                }
            }
            else{
                int p = convert(i,j,0,m);
                int q = convert(i,j,1,m);
                merge(p,q);
                if(i-1>=0){
                    if(a[i-1][j]=='R'){
                        int u = convert(i,j,0,m);
                        int v = convert(i-1,j,0,m);
                        merge(u,v);
                    }
                    else if(a[i-1][j] == 'B'){
                        int u = convert(i,j,1,m);
                        int v= convert(i-1,j,1, m);
                        merge(u,v);
                    }
                    else{
                        int u = convert(i,j,0,m);
                        int v = convert(i-1,j,0,m);
                        merge(u,v);
                        u = convert(i,j,1,m);
                        v = convert(i-1,j,1,m);
                        merge(u,v);
                        u = convert(i,j,0,m);
                        v = convert(i-1,j,1,m);
                        merge(u,v);
                        u = convert(i,j,1,m);
                        v = convert(i-1,j,0,m);
                        merge(u,v);
                    }
                }
                if(j - 1 >= 0){
                    if(a[i][j-1]=='R'){
                        int u = convert(i,j,0,m);
                        int v = convert(i,j-1,0,m);
                        merge(u,v);
                    }
                    else if(a[i][j-1] == 'B'){
                        int u = convert(i,j,1,m);
                        int v= convert(i,j-1,1, m);
                        merge(u,v);
                    }
                    else{
                        int u = convert(i,j,0,m);
                        int v = convert(i,j-1,0,m);
                        merge(u,v);
                        u = convert(i,j,1,m);
                        v = convert(i,j-1,1,m);
                        merge(u,v);
                        u = convert(i,j,0,m);
                        v = convert(i,j-1,1,m);
                        merge(u,v);
                        u = convert(i,j,1,m);
                        v = convert(i,j-1,0,m);
                        merge(u,v);
                    }
                }
                if(i+1<n){
                    if(a[i+1][j]=='R'){
                        int u = convert(i,j,0,m);
                        int v = convert(i+1,j,0,m);
                        merge(u,v);
                    }
                    else if(a[i+1][j] == 'B'){
                        int u = convert(i,j,1,m);
                        int v= convert(i+1,j,1, m);
                        merge(u,v);
                    }
                    else{
                        int u = convert(i,j,0,m);
                        int v = convert(i+1,j,0,m);
                        merge(u,v);
                        u = convert(i,j,1,m);
                        v = convert(i+1,j,1,m);
                        merge(u,v);
                        u = convert(i,j,0,m);
                        v = convert(i+1,j,1,m);
                        merge(u,v);
                        u = convert(i,j,1,m);
                        v = convert(i+1,j,0,m);
                        merge(u,v);
                    }
                }
                if(j+1<m){
                    if(a[i][j+1]=='R'){
                        int u = convert(i,j,0,m);
                        int v = convert(i,j+1,0,m);
                        merge(u,v);
                    }
                    else if(a[i][j+1] == 'B'){
                        int u = convert(i,j,1,m);
                        int v= convert(i,j+1,1, m);
                        merge(u,v);
                    }
                    else{
                        int u = convert(i,j,0,m);
                        int v = convert(i,j+1,0,m);
                        merge(u,v);
                        u = convert(i,j,1,m);
                        v = convert(i,j+1,1,m);
                        merge(u,v);
                        u = convert(i,j,0,m);
                        v = convert(i,j+1,1,m);
                        merge(u,v);
                        u = convert(i,j,1,m);
                        v = convert(i,j+1,0,m);
                        merge(u,v);
                    }
                }
            }
        }
    }
    for(int i = 0 ; i < q ; i ++){
        int r1,c1,r2,c2;cin >> r1 >> c1 >> r2 >> c2 ;
        int u = convert(r1, c1, 1, m);
        int v1 = convert(r2, c2, 0, m);
        int v2 = convert(r2, c2, 1, m);
        if(find_(u) == find_(v1) or find_(u) == find_(v2)){
            cout << "YES" << '\n';
        }
        else cout << "NO" << '\n';
    }
}
signed main(){
    ios_base::sync_with_stdio(0); //DO NOT USE THIS IN INTERACTIVE
    cin.tie(0), cout.tie(0);
    cout << fixed<<setprecision(9);
    int t = 1;
    cin >> t;
    while(t --){
        solve();
    }
}
