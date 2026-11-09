#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using db = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;

template<class T> using V = vector<T>;
template<class T> using pqg = priority_queue<T, vector<T>, greater<T>>;

#define sz(x) int((x).size())
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define pb push_back
#define eb emplace_back

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

void solve() {
    string phase;
    if (!(cin >> phase)) return;

    if (phase == "FIRST") {
        int N;
        cin >> N;
        V<V<int>> adj(N);
        for (int i = 0; i < N - 1; i++) {
            int u, v;
            cin >> u >> v;
            --u; --v;
            adj[u].pb(v);
            adj[v].pb(u);
        }

        // Root the tree at vertex N - 1 (1-indexed: N)
        V<int> A(N, 0);
        auto dfs = [&](auto&& self, int u, int p) -> void {
            for (int v : adj[u]) {
                if (v == p) continue;
                A[v] = u + 1; // Store 1-indexed parent of v
                self(self, v, u);
            }
        };
        dfs(dfs, N - 1, -1);

        // Store XOR checksum of A[0..N-2] in A[N-1]
        // Since A[i] <= 200,000 < 2^18, A[N-1] < 262,144 <= 1,000,000
        int xor_sum = 0;
        for (int i = 0; i < N - 1; i++) {
            xor_sum ^= A[i];
        }
        A[N - 1] = xor_sum;

        for (int i = 0; i < N; i++) {
            cout << A[i] << (i == N - 1 ? '\n' : ' ');
        }
    } else {
        int N;
        cin >> N;
        V<int> A(N);
        int missing_idx = -1;
        int xor_other = 0;

        for (int i = 0; i < N; i++) {
            cin >> A[i];
            if (A[i] == -1) {
                missing_idx = i;
            } else {
                xor_other ^= A[i];
            }
        }

        if (missing_idx != -1) {
            A[missing_idx] = xor_other;
        }

        for (int i = 0; i < N - 1; i++) {
            cout << (i + 1) << " " << A[i] << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
