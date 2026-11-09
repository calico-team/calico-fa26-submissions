#include <bits/stdc++.h>
using namespace std;
struct Trie {
    struct Node {
        int ch[2]={0, 0};
    };
    vector<Node> tr;
    Trie(int n=0) {
        tr.reserve((size_t)(n+5)*31);
        tr.push_back(Node());
    }
    int cloneNode(int x) {
        tr.push_back(tr[x]);
        return (int)tr.size()-1;
    }
    int insert(int root, int x) {
        int newRoot=cloneNode(root);
        int a=newRoot;
        int b=root;
        for(int bit=29; bit>=0; bit--) {
            int c=(x>>bit)&1;
            int oldChild=tr[b].ch[c];
            int newChild=cloneNode(oldChild);
            tr[a].ch[c]=newChild;
            a=newChild;
            b=oldChild;
        }
        return newRoot;
    }
    int maxXor(int root, int x) const {
        int cur=root;
        int res=0;
        for(int bit=29; bit>=0; bit--) {
            int c=(x>>bit)&1;
            int want=c^1;
            if(tr[cur].ch[want]) {
                res|=1<<bit;
                cur=tr[cur].ch[want];
            } else {
                cur=tr[cur].ch[c];
            }
        }
        return res;
    }
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while(T--) {
        int N;
        cin>>N;
        vector<int> A(N), V(N);
        for(int &x:A) {
            cin>>x;
            --x;
        }
        for(int &x:V) {
            cin>>x;
        }
        vector<vector<int>> rev(N);
        vector<int> indeg(N);
        for(int i=0; i<N; i++) {
            rev[A[i]].push_back(i);
            indeg[A[i]]++;
        }
        queue<int> q;
        for(int i=0; i<N; i++) {
            if(indeg[i]==0) {
                q.push(i);
            }
        }
        while(!q.empty()) {
            int u=q.front();
            q.pop();
            int v=A[u];
            if(--indeg[v]==0) {
                q.push(v);
            }
        }
        vector<char> inCycle(N);
        for(int i=0; i<N; i++) {
            inCycle[i]=indeg[i]>0;
        }
        Trie trie(N);
        vector<int> comp(N, -1);
        vector<int> entryPrefix(N);
        vector<int> f(N);
        vector<int> pathRoot(N);
        vector<int> cycleRoot;
        vector<int> cycleXor;
        vector<char> seen(N);
        int comps=0;
        for(int s=0; s<N; s++) {
            if(!inCycle[s]||seen[s]) continue;
            vector<int> cyc;
            int u=s;
            while(!seen[u]) {
                seen[u]=true;
                cyc.push_back(u);
                u=A[u];
            }
            int pref=0;
            int root=0;
            for(int v:cyc) {
                comp[v]=comps;
                entryPrefix[v]=pref;
                root=trie.insert(root, pref);
                pref^=V[v];
            }
            cycleRoot.push_back(root);
            cycleXor.push_back(pref);
            comps++;
        }
        queue<int> bfs;
        for(int i=0; i<N; i++) {
            if(inCycle[i]) {
                bfs.push(i);
            }
        }
        while(!bfs.empty()) {
            int v=bfs.front();
            bfs.pop();
            for(int u:rev[v]) {
                if(comp[u]!=-1) continue;
                comp[u]=comp[v];
                entryPrefix[u]=entryPrefix[v];
                f[u]=V[u]^f[v];
                pathRoot[u]=
                trie.insert(pathRoot[v], f[v]);
                bfs.push(u);
            }
        }
        for(int u=0; u<N; u++) {
            int c=comp[u];
            int ans=0;
            if(inCycle[u]) {
                int x=entryPrefix[u];
                ans=trie.maxXor(cycleRoot[c], x);
            } else {
                int x=f[u]^entryPrefix[u];
                ans=max(
                    ans,
                    trie.maxXor(cycleRoot[c], x)
                );
            }
            if(u) cout<<' ';
            cout<<ans;
        }
        cout<<'\n';
    }
}