#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define all(x) (x).begin(), (x).end()
#define forn(var,start,end) for(int var=start;var<end;var++)
#define X first
#define Y second

vector<int> nxt;
int get(int x){
    while(nxt[x]!=x){
        nxt[x]=nxt[nxt[x]];
        x=nxt[x];
    }
    return x;
}

void solve(){
    int t;
    cin>>t;
    while(t--){
        int n,m,q;
        cin>>n>>m>>q;
        vector<int> r(q),c(q),p(q);
        forn(i,0,q){
            cin>>r[i]>>c[i]>>p[i];
        }

        vector<int> ans(n*m,0);
        nxt.resize(n*(m+1));
        forn(i,0,n*(m+1)) nxt[i]=i;

        for(int i=q-1;i>=0;i--){
            int w=0;
            int power=p[i]*p[i];

            forn(x,r[i]-p[i],r[i]+p[i]+1){
                int d=x-r[i];
                int rem=power-d*d;
                while((w+1)*(w+1)<=rem) w++;
                while(w*w>rem) w--;

                int l=c[i]-w, rr=c[i]+w;
                int base=x*(m+1);
                int pos=get(base+l);

                while(pos<=base+rr){
                    int y=pos-base;
                    int dy=y-c[i];
                    ans[x*m+y]=rem-dy*dy+1;

                    nxt[pos]=get(pos+1);
                    pos=nxt[pos];
                }
            }
        }
        forn(i,0,n){
            forn(g,0,m){
                if(g) cout<<' ';
                cout<<ans[i*m+g];
            }
            cout<<'\n';
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}
