#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    string Phase; int N; cin >> Phase >> N;
    ll D = 1000001 / N, L = 1, Pw = D;
    while (Pw < N) Pw *= D, L++;
    if (Phase == "FIRST") {
        vector<vector<int>> G(N);
        for (int i = 1, u, v; i < N; i++) cin >> u >> v, G[u - 1].push_back(v - 1), G[v - 1].push_back(u - 1);
        vector<int> Par(N, -1), Ord{0};
        for (int i = 0; i < N; i++)
            for (int v : G[Ord[i]])
                if (v != Par[Ord[i]]) Par[v] = Ord[i], Ord.push_back(v);
        vector<ll> Q(N);
        ll S = 0;
        for (int i = 1; i < N; i++) Q[i] = Par[i], S = (S + Q[i]) % N;
        for (int i = 0; i < N; i++) {
            ll c = S;
            for (int j = 0; j < i % L; j++) c /= D;
            cout << Q[i] + N * (c % D) << " \n"[i == N - 1];
        }
    } 
    else {
        vector<ll> A(N), Dg(L, -1);
        int K = -1;
        for (int i = 0; i < N; i++) {
            cin >> A[i];
            if (A[i] < 0) K = i;
            else Dg[i % L] = A[i] / N;
        }
        ll S = 0, Pd = 1, Sum = 0;
        for (int j = 0; j < L; j++) S += Dg[j] * Pd, Pd *= D;
        for (int i = 0; i < N; i++) if (i != K) Sum += A[i] % N;
        A[K] = ((S - Sum) % N + N) % N;
        for (int i = 1; i < N; i++) cout << i + 1 << ' ' << A[i] % N + 1 << '\n';
    }
}