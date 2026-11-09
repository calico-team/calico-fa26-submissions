#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void dfs(ll u, ll prv, vector<ll> &A, vector<vector<ll> > &adjList) {

    A[u] = prv;

    for (auto &v: adjList[u]) {

        if (v == prv) continue;
        dfs(v, u, A, adjList);

    }

}

void first() {

    ll N;
    cin >> N;

    vector<vector<ll> > adjList(N);

    for (ll i = 0; i < N - 1; i++) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    vector<ll> A(N + 1, 0);
    dfs(0, -1, A, adjList);

    A[0] = 0;
    
    // (A[0] = 0) ^ A[2] ^ ... ^ A[N - 1] -> (N - 1) is odd
    // A[1] ^ A[3] ^ ... ^ A[N - 1] -> (N - 1) is even
    for (ll i = (N - 1)%2; i < N; i+=2) {
        A[N] = A[N] ^ A[i];
    }

    for (ll i = 2; i < N; i++) {
        A[i] = A[i] ^ A[i - 1];
    }

    for (ll i = 1; i <= N; i++) {
        if (i != 1) cout << " ";
        cout << A[i];
    }
    cout << endl;

}

void second() {

    // REMINDER: CONSTRUCT ACTUAL TREE BY OUTPUTTING ACTUAL EDGES
    // EDGES ARE 1-INDEXED WHEN OUTPUTTED

    ll N;
    cin >> N;

    vector<ll> A(N + 1);
    for (ll i = 1; i <= N; i++) {
        cin >> A[i];
    }

    vector<ll> p(N, -1); // parent of 1, 2, ..., N-1 = p[1], p[2], ..., p[N-1]

    if (A[N] == -1) { // the back-up is -1'd

        p[1] = A[1];
        for (ll i = 2; i < N; i++) {
            p[i] = A[i] ^ A[i - 1];
        }

    } else {

        ll neg1Ind = -1;
        ll redundancy = A[N];

        for (ll i = 1; i < N; i++) {

            if (A[i] == -1) neg1Ind = i;
            if (A[i] != -1 && A[i - 1] != -1) {
                p[i] = A[i] ^ A[i - 1];
            }

        }

        // cout << "p: ";
        // for (ll i = 1; i < N; i++) {
        //     cout << p[i] << " ";
        // }
        // cout << endl;

        if (neg1Ind == N - 1) {  // N - 1 got nuked

            for (ll i = 2 - ((N - 1) % 2); i < N; i+=2) {
                if (p[i] == -1) continue;
                redundancy ^= p[i];
            }
            p[N - 1] = redundancy;

        } else {

            if (((N - 1) % 2) != (neg1Ind % 2)) neg1Ind++;

            for (ll i = 2 - ((N - 1) % 2); i < N; i+=2) {
                if (p[i] == -1) continue;
                redundancy ^= p[i];
            }
            p[neg1Ind] = redundancy;

            for (ll i = 1; i < N; i++) {
                if (p[i] == -1) {
                    ll totXOR = 0;
                    for (ll j = 1; j < i; j++) {
                        totXOR ^= p[j];
                    }
                    p[i] = A[i+1] ^ p[i+1] ^ totXOR;
                    break;
                }
            }

        }

    }

    for (ll i = 1; i < N; i++) {
        cout << i + 1 << " " << p[i] + 1 << endl;
    }

}

int main() {

    string comms;
    cin >> comms;

    if (comms == "FIRST") {
        first();
    }
    
    if (comms == "SECOND") {
        second();
    }

}