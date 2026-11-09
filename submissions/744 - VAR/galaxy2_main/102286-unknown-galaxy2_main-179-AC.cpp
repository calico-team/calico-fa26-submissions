/*
K3RO
*/

#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <complex>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <optional>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

#define int long long
using ull=unsigned long long;
using ld=long double;
using pii=pair<int,int>;
using vi=vector<int>;
using vvi=vector<vi>;

#define pb push_back
#define fi first
#define se second
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0;i<(n);++i)
#define rng(i,a,b) for(int i=(a);i<(b);++i)
#define per(i,n) for(int i=(n)-1;i>=0;--i)

const bool MULTI=true;
const int MOD=1e9+7;
const int INF=1e18;
mt19937_64 rnd(0xC0FFEEULL);

template<class A,class B> istream& operator>>(istream& i,pair<A,B>& p){ return i>>p.fi>>p.se; }
template<class T> istream& operator>>(istream& i,vector<T>& v){ for(auto& x:v) i>>x; return i; }
template<class T> ostream& operator<<(ostream& o,const vector<T>& v){
    rep(i,sz(v)){ o<<(i?" ":"")<<v[i]; } return o;
}
template<class... T> void input(T&... a){ (cin>>...>>a); }
template<class T,class... Ts> void print(const T& a,const Ts&... b){ cout<<a; ((cout<<' '<<b),...); cout<<'\n'; }
void print(){ cout<<'\n'; }

template<class... T> auto min(T... a){ return std::min({common_type_t<T...>(a)...}); }
template<class... T> auto max(T... a){ return std::max({common_type_t<T...>(a)...}); }
template<class T,class U> bool chmin(T& a,const U& b){ if(b<a){a=b; return true;} return false; }
template<class T,class U> bool chmax(T& a,const U& b){ if(a<b){a=b; return true;} return false; }
int cdiv(int a,int b){ return a/b+((a^b)>0&&a%b); }
int fdiv(int a,int b){ return a/b-((a^b)<0&&a%b); }

int pw(int a,int b,int m=MOD){
    int r=1%m; a%=m; if(a<0) a+=m;
    for(;b>0;b>>=1,a=a*a%m) if(b&1) r=r*a%m;
    return r;
}
int inv(int a,int m=MOD){ return pw(a,m-2,m); }
vi spf;
void sieve(int n){ spf.assign(n+1,0); rng(i,2,n+1) if(!spf[i]) for(int j=i;j<=n;j+=i) if(!spf[j]) spf[j]=i; }

struct chash{
    static ull sm(ull x){ x+=0x9e3779b97f4a7c15; x=(x^(x>>30))*0xbf58476d1ce4e5b9; x=(x^(x>>27))*0x94d049bb133111eb; return x^(x>>31); }
    size_t operator()(ull x) const { static constexpr ull R=0x9e3779b97f4a7c15ULL; return sm(x+R); }
};

struct DSU{
    vi p; DSU(int n=0):p(n,-1){}
    int find(int x){ return p[x]<0?x:p[x]=find(p[x]); }
    bool unite(int a,int b){ a=find(a); b=find(b); if(a==b) return false; if(p[a]>p[b]) swap(a,b); p[a]+=p[b]; p[b]=a; return true; }
    int size(int x){ return -p[find(x)]; }
};
template<class T> struct Compressor{
    vector<T> v;
    void add(const T& x){ v.pb(x); }
    void build(){ sort(all(v)); v.erase(unique(all(v)),v.end()); }
    int get(const T& x) const { return lower_bound(all(v),x)-v.begin(); }
    int size() const { return sz(v); }
};

void solve(){
    int n,m,q;
    cin>>n>>m>>q;
    vector<string> a(n);
    cin>>a;
    vector<array<int,5>> qs(q);
    for(auto& x:qs) for(auto& y:x) cin>>y;
    int v=2*n*m;
    vvi g(v);
    int dr[]={-1,1,0,0},dc[]={0,0,-1,1};
    auto ok=[&](int r,int c,int b){
        return a[r][c]=='.'||a[r][c]==(b?'R':'B');
    };
    rep(r,n) rep(c,m) rep(b,2) if(ok(r,c,b)){
        int u=2*(r*m+c)+b;
        rep(k,4){
            int x=r+dr[k],y=c+dc[k];
            if(x>=0&&x<n&&y>=0&&y<m&&ok(x,y,b))
                g[u].pb(2*(x*m+y)+b);
        }
        if(a[r][c]=='.') g[u].pb(u^1);
    }
    vi ans(q,INF),d(v,-1),qu;
    qu.reserve(v);
    function<void(int,int,vi)> go=[&](int l,int r,vi ids){
        if(l>r||ids.empty()) return;
        int md=(l+r)/2;
        rep(i,n) rep(b,2) if(ok(i,md,b)){
            int s=2*(i*m+md)+b;
            qu.clear();
            qu.pb(s);
            d[s]=0;
            rep(h,sz(qu)){
                int u=qu[h];
                for(int w:g[u]) if(d[w]<0){
                    int c=w/2%m;
                    if(c<l||c>r) continue;
                    d[w]=d[u]+1;
                    qu.pb(w);
                }
            }
            for(int id:ids){
                auto [x,y,z,w,k]=qs[id];
                int s0=2*(x*m+y),t=2*(z*m+w);
                if(d[s0]<0) continue;
                if(d[t]>=0) chmin(ans[id],d[s0]+d[t]);
                if(d[t^1]>=0) chmin(ans[id],d[s0]+d[t^1]);
            }
            for(int u:qu) d[u]=-1;
        }
        vi ls,rs;
        for(int id:ids){
            int x=qs[id][1],y=qs[id][3];
            if(x<md&&y<md) ls.pb(id);
            if(x>md&&y>md) rs.pb(id);
        }
        vi().swap(ids);
        go(l,md-1,move(ls));
        go(md+1,r,move(rs));
    };
    vi ids(q);
    iota(all(ids),0);
    go(0,m-1,move(ids));
    rep(i,q) print(ans[i]<=qs[i][4]?"YES":"NO");
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T=1;
    if(MULTI) cin>>T;
    while(T--) solve();
    return 0;
}