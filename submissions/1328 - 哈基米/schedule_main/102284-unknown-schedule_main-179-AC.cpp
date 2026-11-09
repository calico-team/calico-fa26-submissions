#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    while(T--){
        int N, M, K; cin >> N >> M >> K;
        vector<int> P(N + 1, 0);
        for(int i = 1; i <= N; i++) cin >> P[i];
        vector<vector<int>> ch(N + 1);
        for(int i = 1; i <= N; i++) if(P[i] != 0) ch[P[i]].push_back(i);
        vector<int> tail(N + 1, 0);
        function<int(int)> getTail = [&](int x) -> int {
            if(tail[x]) return tail[x];
            int m = 0;
            for(int c : ch[x]) m = max(m, getTail(c));
            return tail[x] = m + 1;
        };
        for(int i = 1; i <= N; i++) getTail(i);
        priority_queue<pair<int,int>> ready;
        for(int i = 1; i <= N; i++) if(P[i] == 0) ready.push({tail[i], i});
        long long ans = 0;
        vector<int> pending;

        for(int sem = 0; sem < M; sem++){
            int take = min(K, (int)ready.size());
            if(take == 0) break;
            pending.clear();
            for(int t = 0; t < take; t++){
                int id = ready.top().second;
                ready.pop();
                ans++;
                for(int s : ch[id]) pending.push_back(s);
            }
            for(int s : pending) ready.push({tail[s], s});
        }
        cout << ans << "\n";
    }
    return 0;
}
