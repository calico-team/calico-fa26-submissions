#include <bits/stdc++.h>
using namespace std;
using vi=vector<int>;
using lli=long long int;
using pii=pair<int, int>;
using plli=pair<lli, lli>;
using vlli=vector<lli>;
using vpii=vector<pii>;
using vplli=vector<plli>;
using vvi=vector<vi>;
using vvlli=vector<vlli>;
using vc=vector<char>;
using vvc=vector<vc>;
using vb=vector<bool>;
using vvb=vector<vector<bool>>;

class trie{
    private:
        const int bits=5;
        struct node{
            node *l=nullptr;
            node *r=nullptr;
            int c=0;
        };
        node *root;
    public:
        trie(){
            root=new node;
        }
        void insert(int v){
            node *u=root;
            ++root->c;
            for (int i=bits-1; i>=0; --i){
                if (v&(1<<i)){
                    if (u->r==nullptr) u->r=new node;
                    u=u->r;
                }else{
                    if (u->l==nullptr) u->l=new node;
                    u=u->l;
                }
                ++u->c;
            }
        }
        void erase(int v){
            node *u=root;
            --root->c;
            for (int i=bits-1; i>=0; --i){
                if (v&(1<<i)){
                    assert(u->r!=nullptr);
                    u=u->r;
                }else{
                    assert(u->l!=nullptr);
                    u=u->l;
                }
                --u->c;
            }
        }
        int query(int v){
            // over all x in S, returns max(v^x)
            int ans=0;
            node *u=root;
            for (int i=bits-1; i>=0; --i){
                if (v&(1<<i)){
                    if (u->l!=nullptr && u->l->c!=0){
                        u=u->l;
                        ans^=(1<<i);
                    }else u=u->r;
                }else{
                    if (u->r!=nullptr && u->r->c!=0){
                        u=u->r;
                        ans^=(1<<i);
                    }else u=u->l;
                }
                if (u==nullptr) return 0;
            }
            return ans;
        }
};

void test(){
    trie tr;
    tr.insert(5);
    tr.insert(3);
    cout << tr.query(1) << endl;
}

void dfs(vvi &G, int u, vi &A, int s, vi &ans, trie &tr, vi &P, vi &nodes){
    nodes.push_back(u);
    tr.insert(s);
    P[u]=s;
    ans[u]=max(ans[u], tr.query(s));
    for (int v : G[u]) dfs(G, v, A, (s^A[v]), ans, tr, P, nodes);
    tr.erase(s);
}

vi brufo(int n, vi to, vi A){
    vi ans(n, 0);
    for (int i=0; i<n; ++i){
        int s=0;
        int u=i;
        for (int j=0; j<3*n+4; ++j){
            s^=A[u];
            u=to[u];
            ans[i]=max(ans[i], s);
        }
    }
    return ans;
}

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    //test();
    //return 0;
    int tc;
    //tc=-1;
    cin >> tc;
    //mt19937 gen(249);
    while (tc--){
        int n;
        //n=1+gen()%10;
        cin >> n;
        vi to(n);
        for (int i=0; i<n; ++i) cin >> to[i], --to[i];//to[i]=gen()%n;//
        vi A(n);
        for (int i=0; i<n; ++i) cin >> A[i];//A[i]=gen()%16;
        vb vis(n, false);
        vvi aG(n);
        for (int i=0; i<n; ++i){
            aG[i].push_back(to[i]);
            aG[to[i]].push_back(i);
        }
        vvi G(n);
        vb incyc(n, false);
        vi ans(n, 0);
        vi P(n);
        for (int i=0; i<n; ++i){
            if (vis[i]) continue;
            int u=i;
            while (!vis[u]) vis[u]=true, u=to[u];
            vi cyc;
            int p=u;
            u=to[u];
            cyc.push_back(p);
            while (u!=p) cyc.push_back(u), u=to[u];
            u=i;
            while (u!=p) vis[u]=false, u=to[u];
            for (int v : cyc) incyc[v]=true;
            for (int v : cyc) vis[v]=false;
            vi comp;
            queue<int> q;
            q.push(i);
            vis[i]=true;
            while (!q.empty()){
                u=q.front();
                q.pop();
                comp.push_back(u);
                for (int v : aG[u]){
                    if (!vis[v]){
                        vis[v]=true;
                        q.push(v);
                    }
                }
            }
            for (int v : comp){
                if (incyc[v]) continue;
                G[to[v]].push_back(v);
            }
            vi pre(2*cyc.size()+1, 0);
            pre[0]=A[cyc[0]];
            for (int j=1; j<(int)2*cyc.size()+1; ++j) pre[j]=pre[j-1]^A[cyc[j%((int)cyc.size())]];
            trie tra;
            for (int x : pre) tra.insert(x);
            for (int j=0; j<(int)cyc.size(); ++j){
                int v=cyc[j];
                trie tr;
                tr.insert(0);
                vi nodes;
                dfs(G, v, A, A[v], ans, tr, P, nodes);
                for (int w : nodes) ans[w]=max(ans[w], tra.query(P[w]^pre[j]));
            }
        }
        for (int i=0; i<n; ++i) cout << ans[i] << (i==n-1 ? "" : " ");
        cout << endl;
        //vi ans1=brufo(n, to, A);
        //assert(ans==ans1);
    }
}