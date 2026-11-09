#include<bits/stdc++.h>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int n, m, k;
        scanf("%d %d %d", &n, &m, &k);

        vector<vector<int>> children(n + 1);
        vector<int> depth(n + 1, 0);
        vector<int> cnt(n + 1, 0);
        queue<int> q;

        for (int i = 1; i <= n; i++) {
            int p;
            scanf("%d", &p);

            if (p == 0) {
                depth[i] = 1;
                q.push(i);
            } else {
                children[p].push_back(i);
            }
        }

        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            cnt[depth[u]]++;

            for (int v : children[u]) {
                depth[v] = depth[u] + 1;
                q.push(v);
            }
        }

        int available = 0;
        int ans = 0;

        for (int semester = 1; semester <= m; semester++) {
            if (semester <= n) {
                available += cnt[semester];
            }

            ans = min(ans + k, available);
        }

        printf("%d\n", ans);
    }

    return 0;
}
