#include <bits/stdc++.h>
#include <cassert>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int P[10000], dep[10000], depco[10000];
bool visited[10000];

void dfs(int node) {
    if (visited[node]) return;
    visited[node] = true;
    if (P[node] == -1) {
        dep[node] = 0;
    }
    else {
        dfs(P[node]);
        dep[node] = dep[P[node]] + 1;
    }
}

vector<int> graph[10000];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N, M, K;
        cin >> N >> M >> K;
        fill(dep, dep + N, 0);
        fill(depco, depco + N, 0);
        fill(visited, visited + N, false);
        for (int i = 0; i < N; i++) graph[i].clear();
        set<pii> course;
        for (int i = 0; i < N; i++) {
            cin >> P[i];
            P[i]--;
        }

        for (int i = 0; i < N; i++) {
            dfs(i);
            depco[dep[i]]++;
        }

        int ans = 0, tmp = 0;
        for (int i = 0; i < M; i++) {
            if (i < N) tmp += depco[i];
            ans += min(K, tmp);
            tmp -= min(K, tmp);
        }

        cout << ans << '\n';
    }
}