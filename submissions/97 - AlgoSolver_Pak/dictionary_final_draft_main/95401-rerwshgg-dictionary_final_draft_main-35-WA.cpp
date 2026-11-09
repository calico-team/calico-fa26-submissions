#include <bits/stdc++.h>
using namespace std;

struct Trie {
    struct Node { int ch[2]; int cnt; Node(){ ch[0]=ch[1]=-1; cnt=0; } };
    vector<Node> t;
    Trie(){ t.emplace_back(); }
    void insertVal(int x){
        int node = 0;
        t[node].cnt++;
        for(int b=30;b>=0;--b){
            int bit = (x>>b)&1;
            if(t[node].ch[bit]==-1){
                t[node].ch[bit] = (int)t.size();
                t.emplace_back();
            }
            node = t[node].ch[bit];
            t[node].cnt++;
        }
    }
    void eraseVal(int x){
        int node = 0;
        t[node].cnt--;
        for(int b=30;b>=0;--b){
            int bit = (x>>b)&1;
            node = t[node].ch[bit];
            t[node].cnt--;
        }
    }
    int maxXor(int x){
        int node = 0;
        int res = 0;
        for(int b=30;b>=0;--b){
            int bit = (x>>b)&1;
            int want = bit ^ 1;
            if(t[node].ch[want]!=-1 && t[t[node].ch[want]].cnt>0){
                res |= (1<<b);
                node = t[node].ch[want];
            }else{
                node = t[node].ch[bit];
            }
        }
        return res;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if(!(cin >> T)) return 0;
    while(T--){
        int N;
        cin >> N;
        vector<int> A(N+1);
        vector<int> V(N+1);
        for(int i=1;i<=N;i++) cin >> A[i];
        for(int i=1;i<=N;i++) cin >> V[i];

        vector<int> indeg(N+1,0);
        for(int i=1;i<=N;i++) indeg[A[i]]++;

        queue<int> q;
        vector<int> removed(N+1,0);
        for(int i=1;i<=N;i++) if(indeg[i]==0) q.push(i);
        while(!q.empty()){
            int u = q.front(); q.pop();
            removed[u]=1;
            int v = A[u];
            if(--indeg[v]==0) q.push(v);
        }

        vector<int> isCycle(N+1,0);
        for(int i=1;i<=N;i++) if(!removed[i]) isCycle[i]=1;

        vector<vector<int>> rev(N+1);
        for(int i=1;i<=N;i++) rev[A[i]].push_back(i);

        vector<int> ans(N+1,0);
        vector<int> visCycle(N+1,0);

        // Cycle wale hisse
        for(int i=1;i<=N;i++) if(isCycle[i] && !visCycle[i]){
            vector<int> cyc;
            int cur = i;
            while(!visCycle[cur]){
                visCycle[cur]=1;
                cyc.push_back(cur);
                cur = A[cur];
            }
            int m = cyc.size();
            vector<int> pref(m+1,0);
            for(int j=0;j<m;j++) pref[j+1] = pref[j] ^ V[cyc[j]];
            int Xc = pref[m];

            Trie trieC;
            for(int j=0;j<=m;j++) trieC.insertVal(pref[j]);

            // cycle nodes ka answer
            for(int j=0;j<m;j++){
                int Ps = pref[j];
                int best1 = trieC.maxXor(Ps);
                int best2 = trieC.maxXor(Ps ^ Xc);
                ans[cyc[j]] = max(best1, best2);
            }

            // Tail ke liye DFS - har cycle node se bahar
            // hum stack se chalenge, sath me ek trie rakhenge jo cum values ka hai
            for(int j=0;j<m;j++){
                int startCycle = cyc[j];
                // is cycle node se shuru hone wali branches
                // DFS iterative with state
                struct Item{int u; int cum; int state;};
                // hum har child ke liye alag DFS karenge
                for(int child: rev[startCycle]){
                    if(isCycle[child]) continue;
                    Trie triePath;
                    triePath.insertVal(0); // cycle ka cum = 0
                    // manual stack for DFS
                    vector<tuple<int,int,int>> st; // u, cum, iterator index state
                    // hum simple recursion jaisa stack use karte hain
                    // pehle child ko push karo
                    vector<tuple<int,int,int>> stack2;
                    // state 0 = enter, 1 = exit
                    stack2.emplace_back(child, V[child], 0);
                    // cum[child] = V[child] ^ 0 = V[child]
                    // parent cum ko track karne ke liye hume cumParent chahiye
                    // is liye hum cum ko full cum rakhenge
                    while(!stack2.empty()){
                        auto [u, cum, state] = stack2.back();
                        stack2.pop_back();
                        if(state==0){
                            // enter
                            triePath.insertVal(cum);
                            // tail best: cum ^ kisi purani cum se
                            // hume trie me se purani wali nikal kar query karna hai,
                            // is liye pehle apni wali hatate hain? Nahi, humne abhi insert ki hai
                            // Is liye hum query ke liye temporarily apni wali ko ignore karenge:
                            // Asaan tareeqa: query se pehle erase, query ke baad wapas insert
                            // Lekin hum yahan pehle se insert kar chuke hain, to:
                            triePath.eraseVal(cum);
                            int bestTail = triePath.maxXor(cum);
                            triePath.insertVal(cum);

                            int bestC1 = trieC.maxXor(cum);
                            int bestC2 = trieC.maxXor(cum ^ Xc);
                            int bestCyclePart = max(bestC1, bestC2);
                            ans[u] = max(bestTail, bestCyclePart);

                            stack2.emplace_back(u, cum, 1);
                            for(int nxt: rev[u]){
                                if(isCycle[nxt]) continue;
                                int cumNxt = cum ^ V[nxt];
                                stack2.emplace_back(nxt, cumNxt, 0);
                            }
                        }else{
                            triePath.eraseVal(cum);
                        }
                    }
                }
            }
        }

        for(int i=1;i<=N;i++){
            cout << ans[i] << (i==N?'\n':' ');
        }
    }
    return 0;
}