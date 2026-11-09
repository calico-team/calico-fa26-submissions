#include <bits/stdc++.h>
using namespace std;
struct CompressedTrie {
    struct Node {
        int ch[2];
        int bit, val;
        Node() {
            ch[0] =ch[1] =-1;
            bit = -1;
            val =0;
        }
    };
    vector<Node> tr;
    int build(const vector<int>& a,int l, int r) {
        int id =(int)tr.size();
        tr.emplace_back();
        if(l == r) {
            tr[id].val =a[l];
            return id;
        }
        int b = 31 -__builtin_clz((unsigned)(a[l] ^ a[r]));
        int lo =l, hi = r + 1;
        while (lo< hi) {
            int mid = (lo +hi) / 2;
            if ((a[mid] >> b) & 1)hi = mid;
            else lo =mid + 1;
        }
        int m =lo;
        tr[id].bit= b;
        int left= build(a, l, m - 1);
        int right = build(a, m,r);
        tr[id].ch[0] =left;
        tr[id].ch[1]= right;
        return id;
    }
    void init(vector<int> a){
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()),a.end());
        tr.clear();
        tr.reserve(max(1,(int)a.size() * 2));
        build(a, 0, (int)a.size()- 1);
    }
    int query(int x) const{
        int u =0;
        while (tr[u].bit!= -1) {
            int b = tr[u].bit;
            int z= (x >> b)& 1;
            if (tr[u].ch[z ^ 1]!= -1)
                u = tr[u].ch[z^ 1];
            else
                u= tr[u].ch[z];
        }
        return x ^tr[u].val;
    }
};
struct DynamicTrie {
    struct Node {
        int ch[2];
        int cnt;
        Node() {
            ch[0]= ch[1] = -1;
            cnt= 0;
        }
    };
    vector<Node> tr;
    void init(int maxValues){
        tr.clear();
        tr.reserve(1LL + 30LL* maxValues);
        tr.emplace_back();
    }
    void add(int x, int delta) {
        int u = 0;
        tr[u].cnt+= delta;
        for (int b = 29;b >= 0; --b){
            int z = (x >> b)& 1;
            if(tr[u].ch[z] == -1) {
                int id =(int)tr.size();
                tr[u].ch[z] = id;
                tr.emplace_back();
            }
            u = tr[u].ch[z];
            tr[u].cnt += delta;
        }
    }
    int query(int x) const{
        int u = 0;
        int res =0;
        for(int b= 29; b >= 0; --b) {
            int z = (x >> b) & 1;
            int v =tr[u].ch[z ^1];
            if (v != -1 && tr[v].cnt > 0) {
                res |=(1<< b);
                u = v;
            } else {
                u= tr[u].ch[z];
            }
        }
        return res;
    }
};
struct Event {
    int u,p;
    bool exit;
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >>T;
    while (T--) {
        int n;
        cin >>n;
        vector<int> to(n), w(n), indeg(n,0);
        vector<vector<int>> rev(n);
        for(int i =0; i< n; ++i) {
            cin >> to[i];
            --to[i];
            ++indeg[to[i]];
            rev[to[i]].push_back(i);
        }
        for (int i =0; i < n;++i)
            cin >> w[i];
        queue<int> q;
        for (int i =0; i < n; ++i) {
            if (indeg[i]== 0)
                q.push(i);
        }
        while (!q.empty()) {
            int u =q.front();
            q.pop();
            int v= to[u];
            if (--indeg[v] ==0)
                q.push(v);
        }
        vector<char>onCycle(n, false), seenCycle(n, false);
        for(int i= 0; i < n; ++i)
            onCycle[i] = (indeg[i] > 0);
        vector<int> g(n, 0), ans(n,0);
        DynamicTrie pathTrie;
        vector<int> st;
        vector<Event>events;
        for(int i= 0; i < n; ++i) {
            if (!onCycle[i] || seenCycle[i])
                continue;
            vector<int> cyc;
            int x =i;
            do {
                cyc.push_back(x);
                seenCycle[x] = true;
                x= to[x];
            } while (x != i);
            int L =(int)cyc.size();
            vector<int> pref(L);
            vector<int>vals;
            vals.reserve(2* L);
            int S =0;
            for(int j =0; j < L; ++j){
                pref[j] =S;
                vals.push_back(S);
                S ^= w[cyc[j]];
            }
            if (S !=0) {
                for (int j= 0; j < L; ++j)
                    vals.push_back(pref[j] ^S);
            }
            int treeCount =0;
            {
                CompressedTrie cycleTrie;
                cycleTrie.init(vals);
                for (int j= 0; j < L; ++j) {
                    int r =cyc[j];
                    g[r] =pref[j];
                    ans[r]= cycleTrie.query(g[r]);
                }
                st.clear();
                for (int r : cyc) {
                    for (int v : rev[r]){
                        if(!onCycle[v])
                            st.push_back(v);
                    }
                }
                while (!st.empty()) {
                    int u= st.back();
                    st.pop_back();
                    ++treeCount;
                    g[u]= g[to[u]] ^ w[u];
                    ans[u] =cycleTrie.query(g[u]);
                    for (int v : rev[u]) {
                        if(!onCycle[v])
                            st.push_back(v);
                    }
                }
            }
            pathTrie.init(treeCount +1);
            for (int r : cyc) {
                pathTrie.add(0, +1);
                events.clear();
                for(int v : rev[r]) {
                    if (!onCycle[v])
                        events.push_back({v,0, false});
                }
                while (!events.empty()) {
                    Event e =events.back();
                    events.pop_back();
                    if(e.exit) {
                        pathTrie.add(e.p, -1);
                        continue;
                    }
                    int u = e.u;
                    int p =e.p ^ w[u];
                    ans[u]= max(ans[u], pathTrie.query(p));
                    pathTrie.add(p, +1);
                    events.push_back({u, p,true});
                    for (int v : rev[u]) {
                        if (!onCycle[v])
                            events.push_back({v, p,false});
                    }
                }
                pathTrie.add(0, -1);
            }
        }
        for(int i = 0;i < n; ++i) {
            if (i) cout <<' ';
            cout << ans[i];
        }
        cout <<'\n';
    }
    return 0;
}