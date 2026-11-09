#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >>T;
    while (T--){
        int N, M,K;
        cin >>N>> M >> K;
        vector<int> P(N +1);
        vector<vector<int>>children(N+ 1);
        vector<int> sz(N + 1,1);
        for (int i= 1; i<= N; i++) {
            cin >>P[i];
            if(P[i] != 0) {
                children[P[i]].push_back(i);
            }
        }
        for(int i= N; i >= 1; i--) {
            if (P[i] != 0) {
                sz[P[i]] +=sz[i];
            }
        }
        priority_queue<pair<int, int>>pq;
        for(int i = 1; i<= N;i++) {
            if (P[i] ==0) {
                pq.push({sz[i], i});
            }
        }
        int ans= 0;
        for (int semester = 0; semester <M && !pq.empty(); semester++) {
            vector<int> taken;
            int cnt= min(K, (int)pq.size());
            while (cnt--) {
                taken.push_back(pq.top().second);
                pq.pop();
            }
            ans += (int)taken.size();
            for(int u : taken) {
                for (int v : children[u]){
                    pq.push({sz[v], v});
                }
            }
        }
        cout <<ans << '\n';
    }
    return 0;
}