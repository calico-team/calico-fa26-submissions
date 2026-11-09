#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr int maxN = 1e4 + 1;
int N, M, K, T, outDeg[maxN];
vector<int> adj[maxN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    for (int z = 0; z < T; z++)
    {
        cin >> N >> M >> K;
        fill(begin(outDeg), end(outDeg), 0);
        vector<int> ze;
        for (auto & i : adj) i.clear();
        priority_queue<pair<int, int>> q;
        for (int i = 1; i <= N; i++)
        {
            int n; cin >> n;
            adj[n].push_back(i);
            if (n == 0) ze.push_back(i);
            outDeg[n]++;
        }
        for (int i : ze)
        {
            q.emplace(outDeg[i], i);
        }
        int tot = 0;

        for (int i = 0; i < M; i++)
        {
            vector<int> toEmplace;
            int kCount = 0;
            while (!q.empty() && kCount < K)
            {
                auto [deg, n] = q.top(); q.pop();
                kCount++;
                for (int a : adj[n])
                {
                    toEmplace.push_back(a);
                }
            }
            for (int a : toEmplace)
            {
                q.emplace(outDeg[a], a);
            }
            tot += kCount;
        }

        cout << tot << "\n";
    }
}