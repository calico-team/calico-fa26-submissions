#include <bits/stdc++.h>
#include <cassert>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int mod = 1000000;

vector<int> graph[200000];
int par[200000];
void dfs(int node) {
    for (int i : graph[node]) {
        if (i == par[node]) continue;
        par[i] = node;
        dfs(i);
    }
}

int A[200000];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string phase;
    cin >> phase;

    if (phase == "FIRST") {
        int N;
        cin >> N;
        for (int i = 1; i < N; i++) {
            int u, v;
            cin >> u >> v;
            graph[--u].push_back(--v);
            graph[v].push_back(u);
        }
        par[0] = -1;
        dfs(0);

        int Asum = 0;
        for (int i = 1; i < N; i++) {
            Asum += par[i];
            cout << par[i] << ' ';
        }
        cout << Asum % mod << '\n';
    }
    else {
        int N, missingi = -1;
        cin >> N;
        for (int i = 0; i < N; i++) cin >> A[i];

        if (A[N - 1] == -1) for (int i = 0; i < N - 1; i++) cout << A[i] + 1 << ' ' << i + 2 << '\n';
        else {
            vector<pii> ans;
            for (int i = 0; i < N - 1; i++) {
                if (A[i] != -1) {
                    A[N - 1] = (A[N - 1] + mod - A[i]) % mod;
                    ans.push_back({A[i] + 1, i + 2});
                }
                else missingi = i + 1;
            }
            ans.push_back({missingi + 1, A[N - 1] + 1});

            for (pii i : ans) cout << i.first << ' ' << i.second << '\n';
        }
    }
}