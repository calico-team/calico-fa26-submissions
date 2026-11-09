#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define FORR(i,a,b) for(int i=(b)-1;i>=(a);--i)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define bk back()
typedef long long ll;
typedef pair<int,int> pii;
const int N=2e5+5;

int dep[N],par[N],sub[N];
bool vis[N];
int l[N],r[N],ra[N],rb[N],d[N],sd[N];
int c[31][4],who[31],p[31],has[31];

void solve(){
    int n;cin >> n;
    FOR(i,0,n) cin >> l[i];
    FOR(i,0,n) cin>>r[i];
    FOR(g,0,30) has[g]=0;

    int base = 0, ans=0;
    FOR(i,0,n){
        if(l[i] == r[i]){d[i] = -1,base ^= l[i]; continue;}
        d[i]=__lg(l[i]^r[i]);
        int top = (1<<d[i])-1;
        //  2*top+1
        ra[i ] = ~l[i]&top,rb[i]=r[i]&top;
        base ^= l[i]|top; sd[i] = -1; has[d[i]]++;
    }

    FORR(b,0,30){
        FOR(g,b+1,30) FOR(t,0,4) c[g][t]=0;
        int k = 0;
        FOR(i,0,n) if(d[i] > b){
            if(sd[i] >= 0){k += (sd[i]?rb[i]:ra[i])>>b&1; continue;}
            int t = (ra[i]>>b&1)*2+(rb[i]>>b&1);
            c[d[i]][t]++;
            if(t==1 || t == 2) who[d[i]]=i;
        } 
        FOR(g,b+1,30){
            int s = c[g][1]+c[g][2];
            k += c[g][3]+s-(s && !c[g][3] && !c[g][0] && (c[g][1]&1) != p[g]);
        }

        if(has[b]){
            p[b] = !(base>>b&1);
            if(p[b]) base^=(1<<(b+1))-1;
        }
        int q = base>>b&1;
        if(q ? k>=1 : k >= 2){ans |= (1<<(b+1))-1; break;}
        if(q||k) ans |= 1<<b;
        if(!q && k) FOR(g,b+1,30){
            int s = c[g][1]+c[g][2];
            if(s == 1 && !c[g][3] && (c[g][0] || (c[g][1]&1) == p[g])){
                int i = who[g];
                sd[i]=rb[i]>>b&1; p[g]^=sd[i];
            }
        }
    }


    cout << ans << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--) solve();
}
