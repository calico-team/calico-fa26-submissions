#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define all(x) x.begin(), x.end()
#define int long long

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tc=1;
    cin>>tc;
    auto solve=[&]()->void{
        int n;
        int m;
        int q;
        cin>>n>>m>>q;
        vi a(q);
        vi s(q);
        vi d(q);
        for(int i=0;i<q;i++){
            cin>>a[i]>>s[i]>>d[i];
        }
        vector<vi> f(n,vi(m,0));
        vector<vi> g(n,vi(m+1));
        for(int i=0;i<n;i++){
            iota(all(g[i]),0);
        }
        auto z=[&](auto&&z,int w,int e)->int{
            if(g[w][e]==e){
                return e;
            }
            return g[w][e]=z(z,w,g[w][e]);
        };
        auto x=[&](int w)->int{
            int e=sqrtl((long double)w);
            while((__int128)(e+1)*(e+1)<=w){
                e++;
            }
            while((__int128)e*e>w){
                e--;
            }
            return e;
        };
        for(int i=q-1;i>=0;i--){
            int w=a[i];
            int e=s[i];
            int r=d[i];
            int t=max(0LL,w-r);
            int y=min(n-1,w+r);
            for(int j=t;j<=y;j++){
                int o=j-w;
                int p=r*r-o*o;
                int h=x(p);
                int l=max(0LL,e-h);
                int b=min(m-1,e+h);
                int c=z(z,j,l);
                while(c<=b){
                    int v=j-w;
                    int u=c-e;
                    f[j][c]=r*r-v*v-u*u+1;
                    g[j][c]=z(z,j,c+1);
                    c=z(z,j,c);
                }
            }
        }
        for(int i=0;i<n;i++){
            string output="";
            for(int j=0;j<m;j++){
                output+=to_string(f[i][j]);
                if(j+1<m){
                    output+=" ";
                }
            }
            cout<<output<<"\n";
        }
    };
    for(int i=0;i<tc;i++){
        solve();
    }
    return 0;
}