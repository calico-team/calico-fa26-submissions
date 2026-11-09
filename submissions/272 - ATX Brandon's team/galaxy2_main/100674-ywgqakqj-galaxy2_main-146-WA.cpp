#include <bits/stdc++.h>
using namespace std;
const int INF=1e9;
struct Node {
    int l, r,mid;
    int left=-1, right = -1;
    vector<int> dist;
};
struct Solver {
    int N,M, W;
    vector<string> g;
    vector<int> pref, suff;
    vector<Node> nodes;
    int root;
    bool valid(int r, int c,int s) const {
        char ch = g[r][c];
        int mode=s & 1;
        return ch == '.' || (ch=='B' && mode == 0) || (ch == 'R'&&mode==1);
    }
    void floyd(vector<int>& d) {
        for(int k=0;k < W; ++k) {
            int ko = k*W;
            for(int i = 0;i<W;++i) {
                int ik=d[i*W + k];
                if(ik >= INF) continue;
                int io=i * W;
                for(int j=0; j < W;++j) {
                    int kj = d[ko+j];
                    if(kj>=INF) continue;
                    d[io+j]=min(d[io + j], ik+kj);
                }
            }
        }
    }
    vector<int> localColumn(int c) {
        vector<int> d(W*W, INF);
        for(int r=0; r<N; r++) {
            for(int mode = 0;mode<2;++mode) {
                int s=2*r + mode;
                if(!valid(r,c,s)) continue;
                d[s*W+s] = 0;
                if(g[r][c]=='.') d[s*W + (s^1)] = 1;
                if(r+1 < N && valid(r+1,c,s)) {
                    int t=s+2;
                    d[s*W+t] = 1;
                    d[t*W + s]=1;
                }
            }
        }
        floyd(d);
        return d;
    }
    void buildPrefixSuffix() {
        pref.assign((size_t)M*W*W,INF);
        suff.assign((size_t)M * W * W, INF);
        vector<int> prev(W*W,INF);
        for(int c=0;c < M;++c) {
            vector<int> d = localColumn(c);
            if(c > 0) {
                for(int i=0;i<W;++i) {
                    if(!valid(i/2,c-1,i)|| !valid(i/2,c,i)) continue;
                    for(int j = 0; j<W; ++j) {
                        if(prev[i*W+j] >= INF) continue;
                        if(!valid(j/2,c-1,j) || !valid(j/2,c,j)) continue;
                        d[i*W+j]=min(d[i*W+j],prev[i*W+j] + 2);
                    }
                }
                floyd(d);
            }
            copy(d.begin(),d.end(),pref.begin()+(size_t)c*W*W);
            prev.swap(d);
        }
        prev.assign(W*W, INF);
        for(int c=M-1;c>=0;--c) {
            vector<int> d=localColumn(c);
            if(c+1 < M) {
                for(int i = 0;i<W;++i) {
                    if(!valid(i/2,c+1,i)||!valid(i/2,c,i)) continue;
                    for(int j=0;j<W;++j) {
                        if(prev[i*W+j]>=INF) continue;
                        if(!valid(j/2,c+1,j)|| !valid(j/2,c,j)) continue;
                        d[i*W+j] = min(d[i*W+j], prev[i*W+j]+2);
                    }
                }
                floyd(d);
            }
            copy(d.begin(),d.end(),suff.begin()+(size_t)c*W*W);
            prev.swap(d);
        }
    }
    int build(int l,int r) {
        if(l>r) return -1;
        int mid=(l+r)/2;
        int idx=(int)nodes.size();
        nodes.emplace_back();
        nodes[idx].l=l;
        nodes[idx].r = r;
        nodes[idx].mid=mid;
        bool hasLeft=(l>0);
        bool hasRight = (r+1<M);
        int baseCol=hasLeft ? l-1:l;
        int totalCols=(r-l+1)+(int)hasLeft+(int)hasRight;
        int totalStates=totalCols*W;
        int leftOff=hasLeft?0:-1;
        int rightOff=hasRight ? (totalCols-1)*W:-1;
        int interiorStartOff=hasLeft ? W:0;
        nodes[idx].dist.assign((size_t)(r-l+1)*W*W, INF);
        vector<int> d(totalStates, INF);
        using P=pair<int,int>;
        priority_queue<P,vector<P>,greater<P>> pq;
        for(int hub=0;hub<W;++hub) {
            int hr=hub/2;
            if(!valid(hr,mid,hub)) continue;
            fill(d.begin(),d.end(),INF);
            while(!pq.empty()) pq.pop();
            int srcOff=(mid-baseCol)*W+hub;
            d[srcOff]=0;
            pq.push({0,srcOff});
            while(!pq.empty()) {
                auto [du,u]=pq.top();
                pq.pop();
                if(du != d[u]) continue;
                int localCol=u/W;
                int s = u%W;
                int row=s/2;
                int col=baseCol+localCol;
                auto relax=[&](int v,int w) {
                    if(v<0 || v>=totalStates) return;
                    int nd=du+w;
                    if(nd<d[v]) {
                        d[v]=nd;
                        pq.push({nd,v});
                    }
                };
                if(hasLeft && col==l-1) {
                    const int* mat=pref.data()+(size_t)(l-1)*W*W+s*W;
                    for(int t=0;t<W;++t) {
                        if(mat[t]<INF) relax(leftOff+t,mat[t]);
                    }
                    if(valid(row,l,s)) relax(interiorStartOff+s,1);
                    continue;
                }
                if(hasRight && col == r+1) {
                    const int* mat=suff.data()+(size_t)(r+1)*W*W+s*W;
                    for(int t=0;t<W;++t) {
                        if(mat[t] < INF) relax(rightOff+t,mat[t]);
                    }
                    int lastInteriorOff=interiorStartOff+(r-l)*W;
                    if(valid(row,r,s)) relax(lastInteriorOff+s,1);
                    continue;
                }
                if(g[row][col]=='.') relax(localCol*W+(s^1),1);
                if(row>0 && valid(row-1,col,s)) relax(localCol*W+s-2,1);
                if(row+1<N && valid(row+1,col,s)) relax(localCol*W+s+2,1);
                if(col>l) {
                    if(valid(row,col-1,s)) relax((localCol-1)*W+s,1);
                } else if(hasLeft) {
                    if(valid(row,l-1,s)) relax(leftOff+s,1);
                }
                if(col<r) {
                    if(valid(row,col+1,s)) relax((localCol+1)*W+s,1);
                } else if(hasRight) {
                    if(valid(row,r+1,s)) relax(rightOff+s,1);
                }
            }
            for(int col=l;col<=r;++col) {
                int off=(col-baseCol)*W;
                int outBase=((size_t)(col-l)*W)*W+hub;
                for(int s=0;s<W;++s) {
                    nodes[idx].dist[outBase+(size_t)s*W]=d[off+s];
                }
            }
        }
        int lc=(l<mid)?build(l,mid-1):-1;
        int rc=(mid<r) ? build(mid+1,r):-1;
        nodes[idx].left=lc;
        nodes[idx].right = rc;
        return idx;
    }
    void init(vector<string> grid) {
        g=move(grid);
        N=(int)g.size();
        M=(int)g[0].size();
        W=2*N;
        buildPrefixSuffix();
        nodes.clear();
        nodes.reserve(M);
        root=build(0,M-1);
    }
    int query(int sr,int sc,int tr,int tc) const {
        int id=root;
        while(true) {
            const Node& nd=nodes[id];
            if(sc< nd.mid && tc<nd.mid) id=nd.left;
            else if(sc > nd.mid && tc > nd.mid) id=nd.right;
            else break;
        }
        const Node& nd=nodes[id];
        int l=nd.l, mid=nd.mid;
        const vector<int>& tab=nd.dist;
        int startState=2*sr;
        int targets[2];
        int targetCount=0;
        char ch=g[tr][tc];
        if(ch=='.') {
            targets[targetCount++]=2*tr;
            targets[targetCount++] =2 *tr+1;
        }else if(ch=='B') {
            targets[targetCount++]= 2*tr;
        } else if(ch == 'R') {
            targets[targetCount++]=2*tr+1;
        } else return INF;
        const int* ds=tab.data()+ ((size_t)(sc- l)* W+startState)*W;
        int best=INF;
        for(int ti= 0;ti<targetCount;++ti) {
            int ts=targets[ti];
            const int* dt= tab.data()+ ((size_t)(tc-l)* W+ ts)*W;
            for(int i=0;i<W; ++i) {
                if(ds[i]>= INF) continue;
                const int* dm= tab.data()+ ((size_t)(mid-l)*W+i)*W;
                for(int j=0;j<W;++j) {
                    if(dt[j]>=INF || dm[j] >=INF) continue;
                    best=min(best,ds[i]+ dm[j] +dt[j]);
                }
            }
        }
        return best;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while(T--) {
        int N,M,Q;
        cin >> N >> M >> Q;
        vector<string> grid(N);
        for(auto& row : grid) cin>>row;
        Solver solver;
        solver.init(move(grid));
        while(Q--) {
            int rs,cs,re,ce,K;
            cin >> rs>> cs >>re>> ce >>K;
            cout << (solver.query(rs,cs,re,ce)<=K ? "YES":"NO") << '\n';
        }
    }
    return 0;
}