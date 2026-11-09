#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int t,n,m,q;
const int MAXS = 1e6+10;
int a[MAXS], par[MAXS], lvl[MAXS], mx[MAXS], r[MAXS], c[MAXS], p[MAXS];

int root(int x){
    if(par[x] == x) return x;
    par[x] = root(par[x]);
    return par[x];
}

void unite(int x, int y){
    x = root(x), y = root(y);
    if(x == y) return;

    if(lvl[x] < lvl[y]) swap(x,y);
    else if(lvl[x] == lvl[y]) ++lvl[x];
    par[y] = x;
    mx[x] = max(mx[x], mx[y]);
}

int main(){
    cin.tie(0)->sync_with_stdio(0);

    cin >> t;
    while(t--){
        cin >> n >> m >> q;

        bool b = 0;
        if(n > m){
            swap(n,m);
            b = 1;
        }

        for(int i=0; i<n*m; ++i){
            a[i] = 0;
            par[i] = i;
            lvl[i] = 0;
            mx[i] = i%m;
        }

        for(int i=q; i>=1; --i){
            cin >> r[i] >> c[i] >> p[i];
            if(b) swap(r[i],c[i]);
        }
        
        for(int i=1; i<=q; ++i){
            for(int j=-p[i]; j<=p[i]; ++j){
                int d = floor(sqrt(p[i]*p[i]-j*j));
                int cur = mx[root((r[i]+j)*m+c[i]-d)];

                while(cur <= c[i]+d){
                    int curid = (r[i]+j)*m+cur;
                    a[curid] = p[i]*p[i] - j*j - (cur-c[i])*(cur-c[i]) + 1;
                    
                    if(cur+1 < m){
                        int nexid = curid+1;
                        unite(curid,nexid);
                        cur = mx[root(curid)];
                    } else {
                        mx[root(curid)] = m;
                        break;
                    }
                }
            }
        }

        if(b){
            for(int j=0; j<m; ++j) 
                for(int i=0; i<n; ++i)
                    cout << a[i*m+j] << " \n"[i==n-1];
        } else {
            for(int i=0; i<n; ++i)
                for(int j=0; j<m; ++j) 
                    cout << a[i*m+j] << " \n"[j==m-1];
        }
    }
}