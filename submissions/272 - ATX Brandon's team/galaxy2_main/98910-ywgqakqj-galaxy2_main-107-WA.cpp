#include <bits/stdc++.h>
using namespace std;
struct Edge {
    int to, w;
};
struct Solver {
    int N, M,V;
    vector<string> grid;
    vector<int> rankOf,order;
    vector<vector<Edge>> up;
    vector<vector<pair<int,int>>> labels;
    bool valid(int r, int c,int mode) const {
        char ch =grid[r][c];
        return ch == '.' ||
               (ch == 'B' && mode == 0)||
               (ch =='R' && mode== 1);
    }
    int id(int r, int c, int mode) const {
        return (r *M +c) * 2 +mode;
    }
    void makeOrder(int l, int r){
        if(l >r)return;
        int c =(l+ r) / 2;
        makeOrder(l, c - 1);
        makeOrder(c + 1,r);
        for(int row = 0;row <N; ++row) {
            for (int mode = 0; mode < 2; ++mode) {
                if(valid(row, c, mode)){
                    order.push_back(id(row,c, mode));
                }
            }
        }
    }
    void addEdge(int a, int b, int w) {
        if (rankOf[a]< rankOf[b])
            up[a].push_back({b, w});
        else
            up[b].push_back({a, w});
    }
    void init(vector<string> g){
        grid =move(g);
        N =(int)grid.size();
        M = (int)grid[0].size();
        V= 2 * N *M;
        order.clear();
        makeOrder(0, M -1);
        rankOf.assign(V,-1);
        for(int i = 0; i< (int)order.size(); ++i){
            rankOf[order[i]] = i;
        }
        up.assign(V, {});
        for (int r= 0; r <N; ++r) {
            for(int c =0; c< M;++c) {
                for (int mode= 0; mode < 2;++mode){
                    if (!valid(r, c, mode)) continue;
                    int u = id(r, c,mode);
                    if (mode ==0 && grid[r][c] =='.') {
                        addEdge(u, id(r,c, 1),1);
                    }
                    if (r +1< N && valid(r + 1, c, mode)){
                        addEdge(u, id(r + 1, c,mode), 1);
                    }
                    if (c +1 < M && valid(r, c + 1, mode)) {
                        addEdge(u, id(r, c +1, mode), 1);
                    }
                }
            }
        }
        for (int v : order){
            auto &a = up[v];
            sort(a.begin(), a.end(),
                 [](const Edge &x,const Edge &y) {
                     return x.to< y.to;
                 });
            int z =0;
            for (const Edge &e : a){
                if(z && a[z - 1].to ==e.to) {
                    a[z- 1].w = min(a[z - 1].w, e.w);
                } else{
                    a[z++] =e;
                }
            }
            a.resize(z);
            vector<Edge>(a).swap(a);
            int d =(int)a.size();
            for (int i =0; i < d; ++i) {
                for(int j =i + 1; j< d; ++j) {
                    int x = a[i].to;
                    int y= a[j].to;
                    int w = a[i].w +a[j].w;
                    if (rankOf[x]> rankOf[y]) {
                        swap(x, y);
                    }
                    up[x].push_back({y, w});
                }
            }
        }
        labels.assign(V, {});
        vector<int> bestDist(V, 0);
        vector<int> mark(V,0);
        int token =0;
        vector<int>touched;
        touched.reserve(512);
        for (int oi =(int)order.size() - 1; oi >= 0; --oi) {
            int v= order[oi];
            ++token;
            touched.clear();
            mark[v] = token;
            bestDist[v] =0;
            touched.push_back(v);
            for (const Edge &e : up[v]) {
                const auto &lab= labels[e.to];
                for(const auto &p : lab) {
                    int h =order[p.first];
                    int nd = e.w +p.second;
                    if (mark[h] != token) {
                        mark[h] =token;
                        bestDist[h]= nd;
                        touched.push_back(h);
                    } else if (nd <bestDist[h]){
                        bestDist[h] =nd;
                    }
                }
            }
            sort(touched.begin(), touched.end(),
                 [&](int a, int b) {
                     return rankOf[a]< rankOf[b];
                 });
            auto &lab =labels[v];
            lab.reserve(touched.size());
            for(int h : touched) {
                lab.push_back({rankOf[h],bestDist[h]});
            }
        }
        vector<vector<Edge>>().swap(up);
    }
    int query(int sr, int sc,int tr, int tc)const {
        const int INF = 1e9;
        int s = id(sr, sc,0);
        int targets[2];
        int targetCount= 0;
        char ch =grid[tr][tc];
        if (ch =='.') {
            targets[targetCount++] = id(tr, tc, 0);
            targets[targetCount++]= id(tr, tc, 1);
        } else if (ch == 'B'){
            targets[targetCount++]= id(tr, tc, 0);
        } else{
            targets[targetCount++] = id(tr, tc, 1);
        }
        const auto &A =labels[s];
        int ans = INF;
        for(int ti = 0; ti< targetCount; ++ti) {
            const auto &B =labels[targets[ti]];
            size_t i = 0, j= 0;
            while (i < A.size() && j< B.size()) {
                if (A[i].first <B[j].first) {
                    ++i;
                }else if(B[j].first < A[i].first){
                    ++j;
                } else {
                    ans =min(ans, A[i].second +B[j].second);
                    ++i;
                    ++j;
                }
            }
        }
        return ans;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >>T;
    while (T--){
        int N,M, Q;
        cin >> N>> M >> Q;
        vector<string>grid(N);
        for (string &row : grid){
            cin>> row;
        }
        Solver solver;
        solver.init(move(grid));
        while (Q--) {
            int rs,cs,re, ce, K;
            cin >> rs>> cs >> re>> ce >> K;
            cout << (solver.query(rs, cs, re,ce) <= K
                         ? "YES"
                         : "NO")
                 <<'\n';
        }
    }
    return 0;
}