#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct Trie {
    struct Node {
        int child[2];
        int count;

        Node() {
            child[0] = -1;
            child[1] = -1;
            count = 0;
        }
    };

    vector<Node> trie;
    Trie() {trie.push_back(Node());}

    void insert(int x,int val) {
        int node = 0;
        trie[node].count += val;
        for(int i=29; i>=0; i--) {
            int bit = (x >> i) & 1;
            if(trie[node].child[bit] == -1) {
                trie[node].child[bit] = trie.size();
                trie.push_back(Node());
            }
            node = trie[node].child[bit];
            trie[node].count += val;
        }
    }

    int query(int x) {
        int node = 0;
        int ans = 0;
        for(int i=29; i>=0; i--) {
            int bit = (x >> i) & 1;
            int other = 1-bit;
            int next = trie[node].child[other];

            if(next != -1 && trie[next].count > 0) {
                ans += (1 << i);
                node = next;
            }
            else node = trie[node].child[bit];
        }
        return ans;
    }

    void clear() {
        trie.clear();
        trie.push_back(Node());
    }
};

vector<int> solve(int N,vector<int> A,vector<int> V) {
    for(int i=0; i<N; i++) {
        A[i]--;
    }
    vector<vector<int>> rev(N);
    vector<int> indegree(N,0);
    for(int i=0; i<N; i++) {
        rev[A[i]].push_back(i);
        indegree[A[i]]++;
    }
    vector<int> q;

    for(int i=0; i<N; i++) {
        if(indegree[i] == 0) {
            q.push_back(i);
        }
    }

    for(int i=0; i<q.size(); i++) {
        int u = q[i];
        indegree[A[u]]--;

        if(indegree[A[u]] == 0) {
            q.push_back(A[u]);
        }
    }

    vector<bool> cycle(N,false);

    for(int i=0; i<N; i++) {
        cycle[i] = (indegree[i] > 0);
    }

    vector<int> ans(N,0);
    vector<int> dist(N,0);

    Trie cycleTrie;
    Trie treeTrie;

    for(int i=0; i<N; i++) {
        if(!cycle[i] || indegree[i] == -1) {
            continue;
        }

        vector<int> c;
        int u = i;

        do {
            c.push_back(u);
            indegree[u] = -1;
            u = A[u];
        } while(u != i);

        int len = c.size();
        vector<int> pref(len,0);
        int total = 0;

        for(int j=1; j<len; j++) {
            total ^= V[c[j-1]];
            pref[j] = total;
        }

        total ^= V[c[len-1]];

        cycleTrie.clear();

        for(int j=0; j<len; j++) {
            cycleTrie.insert(pref[j],1);
            cycleTrie.insert(pref[j]^total,1);
        }

        for(int j=0; j<len; j++) {
            int next = (j+1)%len;
            ans[c[j]] = cycleTrie.query(V[c[j]]^pref[next]);
        }
        treeTrie.clear();
        treeTrie.insert(0,1);

        stack<pair<int,bool>> st;

        for(int root : c) {
            dist[root] = 0;
            st.push({root,false});

            while(!st.empty()) {
                int v = st.top().first;
                bool done = st.top().second;
                st.pop();

                if(done) {
                    treeTrie.insert(dist[v],-1);
                    continue;
                }

                for(int child : rev[v]) {
                    if(cycle[child]) {
                        continue;
                    }

                    dist[child] = dist[v]^V[child];

                    int best = treeTrie.query(V[child]^dist[v]);
                    best = max(best,cycleTrie.query(V[child]));

                    ans[child] = best;
                    st.push({child,false});
                }

                treeTrie.insert(dist[v],1);
                st.push({v,true});
            }
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<int> A(N), V(N);

        for (int& i : A) cin >> i;
        for (int& i : V) cin >> i;

        vector<int> ans = solve(N, A, V);

        for (int& i : ans) cout << i << ' ';
        cout << '\n';
    }
    return 0;
}
