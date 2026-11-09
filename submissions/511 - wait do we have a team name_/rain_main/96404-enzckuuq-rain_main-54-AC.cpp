#include <bits/stdc++.h>
using namespace std;

////////////////////
//SHORT
#define int long long
// #define int __int128_t
#define all(v) (v).begin(), (v).end()
#define sz(x) (int)(x).size()
#define lsb(x) ((x)&(-(x)))
typedef pair<int, int> pi;
typedef array<int, 3> a3;
typedef array<int, 4> a4;
using ll=long long;
using ld=long double;
using i128=__int128_t;
//DEBUG
bool dbg=false;
#define debug(x) do {if (dbg) cerr<<#x<<": "<<(x)<<'\n';} while (false)
//CONST
const int INF=0x3f3f3f3f, MOD=1e9+7;
//RANDOM
random_device rd;
mt19937 rng(rd());
uniform_real_distribution<float> distf(0.0f, 1.0f);
//POW
int powmod(int b, int e){
    int ret=1;
    while (e){
        if (e&1) ret=(1LL*ret*b)%MOD;
        b=(1LL*b*b)%MOD; e>>=1;
    }
    return ret;
}
////////////////////


/*
consider the 2d plane
moving on z doesn't matter
all you want to know is that, after movement, how many distinct positions there are
some drones move upwards and some drones move rightward, separate them
drones moving up never block others going up, same for right
question: when does a drone block another drone? how many times?
consider an up drone that starts at (x1, y1)
consider a right drone that starts at (x2, y2)
after k steps, the up drone will be at (x1, y1+k)
right at (x2+k, y2)
these two drones overlap at step k if:
x1=x2+k
y1+k=y2
<=> they overlap if y2-y1==x1-x2
x1+y1==x2+y2 and y2-y1<k
never a multi-overlap of >2
each of the k nights, each drone collects 1
however, for each pairwise overlap that will ever occur, -1
maintain a map of {x+y:{vector of all y positions}}
for each rightgoer, count how many upgoers
i.e. count how many have the same x+y, and also have y1>=y2-k
*/
int t;
signed main(){
    //cin.tie(0); ios_base::sync_with_stdio(0);
    cin>>t;
    for (int _=0;_<t;_++){
        int n, k; cin>>n>>k;
        map<int, vector<int>> upgoer;
        vector<pi> c{};
        for (int i=0;i<n;i++){
            int xi, yi, zi; char di; cin>>xi>>yi>>zi>>di;
            if (di=='N'){
                upgoer[xi+yi].push_back(yi);
            } else{
                c.push_back({xi, yi});
            }
        }
        for (auto [xx, _]:upgoer) sort(all(upgoer[xx]));
        int ans=n*k;
        for (auto [x, y]:c){
            int lb=(lower_bound(all(upgoer[x+y]), y-k+1)-upgoer[x+y].begin());
            int ub=(lower_bound(all(upgoer[x+y]), y)-upgoer[x+y].begin());
            ans-=ub-lb;
        }
        cout<<ans<<'\n';
    }
    return 0;
}