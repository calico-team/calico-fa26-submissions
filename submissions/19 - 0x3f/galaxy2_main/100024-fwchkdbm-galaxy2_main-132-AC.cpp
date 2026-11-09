#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <cstring>
#include <map>
#include <bitset>
#include <set>
#include <queue>
#include <cmath>
#include <tuple>
#include <stack>
#include <numeric>
#include <climits>
#include <deque> 
#include <chrono>
#include <unordered_map>
#include <cstring>
#include <random>
using namespace std;
void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#define systemwait system("read -p \"Press Enter to continue...\"");
#define debugbreak exit(0)
#else
#define debug(x...) 
#define systemwait
#define debugbreak
#endif

#define LL long long
#define endl '\n'
#define all(x) (x).begin(),(x).end()
#define sqsq(x) (x)*(x)
#define pii pair<int,int>
#define vi vector<int>
#define vii vector<pii>
#define tiii tuple<int,int,int>
#define vstto vector<Edge>
#define fi first
#define se second
#define pb push_back

const int INF=1e9+7;
const int MOD=1e9+7;
//const int MOD=998244353;
const int dx[4]={0,(-1),0,1};
const int dy[4]={(-1),0,1,0};
const int maxch=26;
const int maxn=15;
const int maxm=4005;

int N,M,Q;
char mp[maxn][maxm];
vector<vi> dist[maxm*4];

bool inbounds(int x,int y,int z) {
    return mp[x][y]=='.' || mp[x][y]=='R' && z==0 || mp[x][y]=='B' && z==1;
}

int getid(int x,int y, int z, int L) {
    return x*2+N*2*(y-L)+z;
}

void build(int p, int L, int R) {
    if(L>R) {
        return;
    }
    int mid=(L+R)/2,len=R-L+1;
    dist[p].assign(N*2,vi(N*2*len,INF));
    for(int x=0;x<N;x++) {
        for(int z=0;z<2;z++) {
            if(!inbounds(x,mid,z)) {
                continue;
            }
            queue<tuple<int,int,int>> q;
            q.push({x,mid,z});
            auto &d=dist[p][z+x*2];
            d[getid(x,mid,z,L)]=0;
            while(!q.empty()) {
                auto [curx,cury,curz]=q.front();
                q.pop();
                int u=getid(curx,cury,curz,L);
                if(mp[curx][cury]=='.') {
                    int v=getid(curx,cury,curz^1,L);
                    if(d[v]==INF) {
                        d[v]=d[u]+1;
                        q.push({curx,cury,curz^1});
                    }
                }
                for(int dir=0;dir<4;dir++) {
                    int nx=curx+dx[dir];
                    int ny=cury+dy[dir];
                    if(nx>=0 && nx<N && ny>=L && ny<=R && inbounds(nx,ny,curz)) {
                        int v=getid(nx,ny,curz,L);
                        if(d[v]==INF) {
                            d[v]=d[u]+1;
                            q.push({nx,ny,curz});
                        }
                    }
                }
            }
        }
    }
    build(p*2,L,mid-1);
    build(p*2+1,mid+1,R);
}

int ans;
void query(int p, int L, int R, int x1, int y1, int x2, int y2) {
    int mid=(L+R)/2;
    int u=getid(x1,y1,1,L);
    for(int x=0;x<N;x++) {
        for(int z=0;z<2;z++) {
            auto &d=dist[p][x*2+z];
            if(inbounds(x,mid,z) && d[u]!=INF) {
                for(int nz=0;nz<2;nz++) {
                    if(inbounds(x2,y2,nz)) {
                        int v=getid(x2,y2,nz,L);
                        ans=min(ans,d[u]+d[v]);
                    }
                }
            }
        }
    }
    if(y1<mid && y2<mid) {
        query(p*2,L,mid-1,x1,y1,x2,y2);
    }
    if(y1>mid && y2>mid) {
        query(p*2+1,mid+1,R,x1,y1,x2,y2);
    }
}

void solve() {
//--------Initiallize--------
//--------Input--------
    cin>>N>>M>>Q;
    for(int i=0;i<N;i++) {
        for(int j=0;j<M;j++) {
            cin>>mp[i][j];
        }
    }
    build(1,0,M-1);
    for(int i=1;i<=Q;i++) {
        int x1,y1,x2,y2,k;
        cin>>x1>>y1>>x2>>y2>>k;
        ans=INF;
        query(1,0,M-1,x1,y1,x2,y2);
        if(ans<=k) {
            cout<<"YES"<<endl;
        } else {
            cout<<"NO"<<endl;
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int TT=1;
    cin>>TT;
    for(int i=1;i<=TT;++i) {
        solve();
    }
    return 0;
}