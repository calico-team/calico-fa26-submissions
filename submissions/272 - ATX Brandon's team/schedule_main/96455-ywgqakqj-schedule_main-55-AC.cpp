#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >>T;
    while (T--){
        int N,M, K;
        cin >> N>>M >> K;
        vector<vector<int>>children(N +1);
        vector<int> roots;
        for(int i =1;i <= N; i++) {
            int p;
            cin >>p;
            if(p== 0) {
                roots.push_back(i);
            } else {
                children[p].push_back(i);
            }
        }
        vector<int> order;
        order.reserve(N);
        vector<int> st =roots;
        while(!st.empty()) {
            int u =st.back();
            st.pop_back();
            order.push_back(u);
            for(int v : children[u]) {
                st.push_back(v);
            }
        }
        vector<int> sz(N +1, 1);
        for(int i = (int)order.size() - 1; i >= 0;i--) {
            int u= order[i];
            for(int v : children[u]) {
                sz[u] +=sz[v];
            }
        }
        priority_queue<pair<int, int>> pq;
        for (int r : roots) {
            pq.push({sz[r], r});
        }
        long long ans = 0;
        for(int semester =0; semester <M && !pq.empty(); semester++) {
            vector<int> taken;
            int cnt =min(K, (int)pq.size());
            while(cnt--) {
                taken.push_back(pq.top().second);
                pq.pop();
            }
            ans+= taken.size();
            for(int u : taken) {
                for (int v : children[u]) {
                    pq.push({sz[v], v});
                }
            }
        }
        cout <<ans<< '\n';
    }
    return 0;
}