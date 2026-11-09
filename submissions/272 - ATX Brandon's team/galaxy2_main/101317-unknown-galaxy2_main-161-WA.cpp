#include <bits/stdc++.h>
using namespace std;
const int INF=1e9;
struct Boundary {
    int leftCol=-1, rightCol = -1;
    int leftCnt = 0,rightCnt=0;
    vector<int> ids;
    vector<int> d;
};
struct Node {
    int l,r, c;
    int leftChild= -1, rightChild= -1;
    vector<int> states;
    vector<int> D,labels;
};
struct Solver{
    int N,M, W;
    vector<string> grid;
    vector<Node> nodes;
    int root= -1;
    bool valid(int col,int s) const {
        if(s<0 || s >= W || col< 0 ||col>=M) return false;
        char ch= grid[s /2][col];
        int mode = s& 1;
        return ch=='.' || (ch=='B' && mode==0) || (ch =='R'&&mode== 1);
    }
    int build(int l,int r,const Boundary &bd){
        if(l>r) return -1;
        int c =(l+ r)/2;
        vector<int> states(W);
        iota(states.begin(),states.end(),0);
        const int S= W;
        const int len=r-l +1;
        const int intervalSlots =len*W;
        const int B= (int)bd.ids.size();
        const int total = intervalSlots+ B;
        auto getIndex = [&](int col,int s) ->int {
            if (col>=l && col <=r) return (col-l)*W+ s;
            if(bd.leftCol!= -1 && col== bd.leftCol) return intervalSlots+s;
            if(bd.rightCol!=-1 && col ==bd.rightCol) return intervalSlots+bd.leftCnt+ s;
            return -1;
        };
        Node node;
        node.l=l;
        node.r =r;
        node.c =c;
        node.states= states;
        node.D.assign(S* S,INF);
        node.labels.assign((size_t)intervalSlots*S, INF);
        vector<int> cross((size_t)S* B,INF);
        for (int si= 0;si<S;++si) {
            if(!valid(c,states[si])) continue;
            vector<int> dist(total,INF);
            using P= pair<int,int>;
            priority_queue<P,vector<P>, greater<P>> pq;
            int startIdx=(c -l)* W+states[si];
            dist[startIdx]= 0;
            pq.push({0,startIdx});
            auto relax= [&](int u,int nd,int w) {
                if(u<0 || w>= INF) return;
                int cand=nd+w;
                if (cand<dist[u]) {
                    dist[u]= cand;
                    pq.push({cand,u});
                }
            };
            while(!pq.empty()) {
                auto [du,u]= pq.top();
                pq.pop();
                if(du !=dist[u]) continue;
                if (u<intervalSlots) {
                    int col=l+u/W;
                    int s=u %W;
                    int row=s /2;
                    if(row>0 && valid(col,s-2)) relax(u-2,du, 1);
                    if (row+ 1<N &&valid(col,s+2)) relax(u+ 2,du,1);
                    if(grid[row][col]== '.') {
                        int ns= s^1;
                        if (valid(col,ns)) relax((col -l)*W+ ns,du,1);
                    }
                    if(col > 0 && valid(col-1,s)) relax(getIndex(col-1,s),du,1);
                    if (col+1 <M && valid(col+1, s)) relax(getIndex(col+ 1,s), du,1);
                } else{
                    int bi= u- intervalSlots;
                    int col= (bi <bd.leftCnt)?bd.leftCol:bd.rightCol;
                    int s=bd.ids[bi]% W;
                    if (col ==l -1&& l>= 0 && valid(l,s)) relax(getIndex(l,s),du,1);
                    if(col== r+1 && r+1<M && valid(r, s)) relax(getIndex(r,s),du, 1);
                    for(int bj=0;bj <B; ++bj){
                        int w= bd.d[(size_t)bi*B+ bj];
                        if(w<INF) relax(intervalSlots+bj,du,w);
                    }
                }
            }
            for(int off =0;off<intervalSlots; ++off) {
                node.labels[(size_t)off*S+si]=dist[off];
            }
            for (int sj=0;sj<S; ++sj) {
                int off =(c-l)* W+ states[sj];
                node.D[(size_t)si * S+sj]=dist[off];
            }
            for(int bj=0;bj<B; ++bj) {
                cross[(size_t)si*B+ bj]= dist[intervalSlots+bj];
            }
        }
        int me= (int)nodes.size();
        nodes.push_back(move(node));
        if(l <=c-1) {
            Boundary child;
            child.leftCol=bd.leftCol;
            child.rightCol=c;
            child.leftCnt= bd.leftCnt;
            child.rightCnt= W;
            for(int i=0;i<bd.leftCnt;++i) child.ids.push_back(bd.ids[i]);
            for ( int s:states) child.ids.push_back(c* W+s);
            int C=(int)child.ids.size();
            child.d.assign((size_t)C * C,INF);
            for(int i = 0;i<bd.leftCnt; ++i) {
                for(int j =0;j<bd.leftCnt; ++j) {
                    child.d[(size_t)i *C +j]=bd.d[(size_t)i*B+ j];
                }
            }
            for(int i=0;i< S; ++i) {
                for (int j =0;j<S;++j) {
                    child.d[(size_t)(bd.leftCnt+i)* C +(bd.leftCnt+ j)]=nodes[me].D[(size_t)i*S+j];
                }
            }
            for(int i=0;i<bd.leftCnt;++i) {
                for (int j =0;j<S; ++j) {
                    int d=cross[(size_t)j*B+i];
                    child.d[(size_t)i*C+(bd.leftCnt+j)]=d;
                    child.d[(size_t)(bd.leftCnt+j)*C + i] =d;
                }
            }
            nodes[me].leftChild=build(l,c-1,child);
        }
        if(c+1<=r) {
            Boundary child;
            child.leftCol=c;
            child.rightCol=bd.rightCol;
            child.leftCnt= W;
            child.rightCnt= bd.rightCnt;
            for(int s:states) child.ids.push_back(c *W+ s);
            for (int i=0;i<bd.rightCnt;++i) child.ids.push_back(bd.ids[bd.leftCnt+i]);
            int C= (int)child.ids.size();
            child.d.assign((size_t)C * C,INF);
            for(int i=0;i<S; ++i) {
                for(int j=0;j < S;++j) {
                    child.d[(size_t)i *C+j]=nodes[me].D[(size_t)i*S+ j];
                }
            }
            for (int i=0;i<bd.rightCnt;++i) {
                for(int j=0;j<bd.rightCnt;++j){
                    child.d[(size_t)(S+i)* C +(S+j )]=bd.d[(size_t)(bd.leftCnt+i) *B+ (bd.leftCnt+j)];
                }
            }
            for(int i=0;i<S; ++i) {
                for(int j=0;j< bd.rightCnt;++j) {
                    int d= cross[(size_t)i*B+(bd.leftCnt +j)];
                    child.d[(size_t)i*C+(S+ j)]=d;
                    child.d[(size_t)(S+ j)*C+ i]=d;
                }
            }
            nodes[me].rightChild=build(c+1,r,child);
        }
        return me;
    }
    void init(int n,int m,vector<string> g) {
        N =n;
        M= m;
        W=2* N;
        grid=move(g);
        nodes.clear();
        nodes.reserve(2*M+5);
        Boundary empty;
        root=build(0,M-1,empty);
    }
    int queryDistance(int rs,int cs,int re,int ce) const {
        int startState= rs *2;
        if (!valid(cs,startState)) return INF;
        vector<int> targetStates;
        char ch= grid[re][ce];
        if(ch== '.') {
            targetStates.push_back(re*2);
            targetStates.push_back(re*2+1);
        } else if (ch =='B') {
            targetStates.push_back(re*2);
        }else {
            targetStates.push_back(re*2+1);
        }
        int lo= min(cs,ce), hi=max(cs,ce);
        int id=root;
        while(true)  {
            const Node &nd=nodes[id];
            if(nd.c>=lo && nd.c<=hi) break;
            if (hi< nd.c) id=nd.leftChild;
            else id= nd.rightChild;
        }
        const Node &nd=nodes[id];
        int S=(int)nd.states.size();
        int startOff= ((cs-nd.l)*W+startState)*S;
        int best =INF;
        for(int targetState:targetStates) {
            int targetOff=((ce-nd.l)*W+targetState)*S;
            for (int i =0;i<S;++i) {
                int ds=nd.labels[startOff+i];
                if(ds>= INF) continue;
                for(int j=0;j < S;++j) {
                    int dt=nd.labels[targetOff+j];
                    int mid=nd.D[(size_t)i* S+j];
                    if(dt >=INF || mid>= INF) continue;
                    best= min(best,ds+mid+dt);
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
        int N,M, Q;
        cin >> N >>M>> Q;
        vector<string> grid(N);
        for (auto &row:grid) cin >> row;
        Solver solver;
        solver.init(N,M,move(grid));
        while(Q--){
            int rs,cs, re,ce;
            long long K;
            cin >> rs >>cs >>re >> ce >>K;
            int d =solver.queryDistance(rs, cs,re,ce);
            cout<<(d<=K ? "YES":"NO") <<'\n';
        }
    }
    return 0;
}