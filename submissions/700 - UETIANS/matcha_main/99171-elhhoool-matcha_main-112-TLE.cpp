#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

typedef long long ll;
typedef pair<int,int> P;

// memo keyed by (hash of sorted ranges, bit)
static unordered_map<ll, int> memo;

static ll hashRanges(const vector<P>& r){
    ll h = 1469598103934665603ULL; // FNV-ish
    for (auto &p : r){
        ll v = ((ll)p.first<<20) ^ (ll)p.second;
        h ^= v; h *= 1099511628211ULL;
    }
    return h;
}

static int solveRec(vector<P> ranges, int bit){
    if (bit < 0) return 0;
    int full = (bit>=30)?0x7fffffff:((1<<(bit+1))-1);
    for (auto &p : ranges) if (p.first==0 && p.second==full) return full; // free -> all ones
    sort(ranges.begin(), ranges.end());
    ll key = hashRanges(ranges) ^ ((ll)bit*1000000007LL);
    auto it = memo.find(key);
    if (it != memo.end()) return it->second;

    int mask = (1<<bit)-1;
    int fixedPar = 0;
    vector<P> fixedLowers;
    // straddlers grouped by their (opt0, opt1) option pair -> count
    // opt0 = (first&mask, mask), opt1 = (0, second&mask); group key = (first&mask, second&mask)
    vector<pair<P,int>> groups;        // ((lowL, lowR), count)
    {
        vector<P> strad;               // (lowL, lowR)
        for (auto &p : ranges){
            int ab=(p.first>>bit)&1, bb=(p.second>>bit)&1;
            if (ab==bb){ fixedPar^=ab; fixedLowers.push_back({p.first&mask, p.second&mask}); }
            else strad.push_back({p.first&mask, p.second&mask});
        }
        if (strad.empty()){
            int lower = solveRec(fixedLowers, bit-1);
            int r = (fixedPar<<bit) | lower;
            memo[key]=r; return r;
        }
        sort(strad.begin(), strad.end());
        for (size_t i=0;i<strad.size();){
            size_t j=i; while (j<strad.size() && strad[j]==strad[i]) ++j;
            groups.push_back({strad[i], (int)(j-i)});
            i=j;
        }
    }
    int k = 0; for (auto &g : groups) k += g.second;   // total straddlers
    int need = 1 ^ fixedPar;
    int best = 0;

    // Helper: build full lower-set for a routing where each group is all-opt0,
    // except groups flagged in `flipGroup` have exactly one member on opt1.
    unordered_map<ll,char> tried;
    auto evalAll0 = [&](int flipG /*-1 none*/){
        vector<P> low = fixedLowers;
        low.reserve(fixedLowers.size()+k);
        for (int gi=0; gi<(int)groups.size(); ++gi){
            P o0 = {groups[gi].first.first, mask};
            P o1 = {0, groups[gi].first.second};
            int cnt = groups[gi].second;
            if (gi==flipG){ low.push_back(o1); --cnt; }
            for (int t=0;t<cnt;t++) low.push_back(o0);
        }
        sort(low.begin(), low.end());
        ll h = hashRanges(low);
        if (tried.count(h)) return;
        tried[h]=1;
        int v = solveRec(low, bit-1);
        if (v>best) best=v;
    };
    auto evalAll1 = [&](int flipG){
        vector<P> low = fixedLowers;
        low.reserve(fixedLowers.size()+k);
        for (int gi=0; gi<(int)groups.size(); ++gi){
            P o0 = {groups[gi].first.first, mask};
            P o1 = {0, groups[gi].first.second};
            int cnt = groups[gi].second;
            if (gi==flipG){ low.push_back(o0); --cnt; }
            for (int t=0;t<cnt;t++) low.push_back(o1);
        }
        sort(low.begin(), low.end());
        ll h = hashRanges(low);
        if (tried.count(h)) return;
        tried[h]=1;
        int v = solveRec(low, bit-1);
        if (v>best) best=v;
    };

    // all-opt0 (parity 0); if need==1 flip one representative of each distinct group
    if (0==need) evalAll0(-1);
    else for (int gi=0; gi<(int)groups.size() && best<mask; ++gi) evalAll0(gi);
    // all-opt1 (parity k&1); if mismatched flip one representative of each distinct group
    if (best<mask){
        if ((k&1)==need) evalAll1(-1);
        else for (int gi=0; gi<(int)groups.size() && best<mask; ++gi) evalAll1(gi);
    }
    int res = (1<<bit) | best;
    memo[key]=res; return res;
}

int solve(int N, vector<int> L, vector<int> R){
    memo.clear();
    // dedup identical ranges early (XOR pairs cancel? NO - keep all; dedup only helps memo, not correctness)
    vector<P> ranges(N);
    for (int i=0;i<N;i++) ranges[i]={L[i],R[i]};
    return solveRec(ranges, 29);
}

int main(){
    int T;
    if(scanf("%d",&T)!=1) return 0;
    while(T--){
        int N; scanf("%d",&N);
        vector<int> L(N), R(N);
        for(auto&x:L) scanf("%d",&x);
        for(auto&x:R) scanf("%d",&x);
        printf("%d\n", solve(N,L,R));
    }
    return 0;
}
