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

struct Trie{
    struct Node{ int32_t ch[2]={0,0},cnt=0; };
    vector<Node> t;
    Trie(){ t.push_back(Node()); }
    void add(int x,int d){
        int u=0;
        t[u].cnt+=d;
        per(b,30){
            int c=x>>b&1;
            if(!t[u].ch[c]){
                t[u].ch[c]=sz(t);
                t.push_back(Node());
            }
            u=t[u].ch[c];
            t[u].cnt+=d;
        }
    }
    int qry(int x){
        int u=0,r=0;
        per(b,30){
            int c=x>>b&1,w=t[u].ch[c^1];
            if(w&&t[w].cnt>0) r|=1LL<<b,u=w;
            else u=t[u].ch[c];
        }
        return r;
    }
};

void solve(){
    int n;
    cin>>n;
    vi a(n),v(n),in(n),hd(n,-1),nx(n),p(n),ans(n),vis(n);
    cin>>a>>v;
    rep(i,n){
        --a[i];
        ++in[a[i]];
        nx[i]=hd[a[i]];
        hd[a[i]]=i;
    }
    queue<int> q;
    rep(i,n) if(!in[i]) q.push(i);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        if(!--in[a[u]]) q.push(a[u]);
    }
    rep(s,n) if(in[s]&&!vis[s]){
        vi cy;
        int u=s,z=0;
        do{
            vis[u]=1;
            cy.pb(u);
            p[u]=z;
            z^=v[u];
            u=a[u];
        }while(u!=s);
        Trie tr;
        for(int x:cy){
            tr.add(p[x],1);
            tr.add(p[x]^z,1);
        }
        for(int x:cy){
            ans[x]=tr.qry(p[x]);
            vector<pii> st;
            for(int y=hd[x];y!=-1;y=nx[y]) if(!in[y]) st.pb({y,0});
            while(!st.empty()){
                auto [y,e]=st.back();
                st.pop_back();
                if(e){ tr.add(p[y],-1); continue; }
                p[y]=v[y]^p[a[y]];
                tr.add(p[y],1);
                ans[y]=tr.qry(p[y]);
                st.pb({y,1});
                for(int w=hd[y];w!=-1;w=nx[w]) if(!in[w]) st.pb({w,0});
            }
        }
    }
    print(ans);
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T=1;
    if(MULTI) cin>>T;
    while(T--) solve();
    return 0;
}