#include <iostream>
#include <vector>
#include <string>

using namespace std;

void solve_first() {
    int n;
    if (!(cin >> n)) return;

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> parent(n + 1, 0);
    vector<int> q; 
    q.push_back(1);
    parent[1] = -1; 

    int head = 0;
    while (head < q.size()) {
        int u = q[head++];
        for (int v : adj[u]) {
            if (parent[v] == 0) { 
                parent[v] = u;    
                q.push_back(v);
            }
        }
    }

    vector<int> A(n, 0);
    int xor_sum = 0;
    
    for (int i = 2; i <= n; i++) {
        A[i - 1] = parent[i]; 
        xor_sum ^= parent[i]; 
    }
    
    A[0] = xor_sum; 

    for (int i = 0; i < n; i++) {
        cout << A[i] << (i == n - 1 ? "" : " ");
    }
    cout << "\n";
}

void solve_second() {
    int n;
    if (!(cin >> n)) return;

    vector<int> A(n);
    int missing_idx = -1;
    int current_xor = 0;

    for (int i = 0; i < n; i++) {
        cin >> A[i];
        if (A[i] == -1) {
            missing_idx = i;
        } else {
            current_xor ^= A[i]; 
        }
    }

    A[missing_idx] = current_xor;

    for (int i = 1; i < n; i++) {
        cout << i + 1 << " " << A[i] << "\n";
    }
}

int main() {
    string phase;
    if (cin >> phase) {
        if (phase == "FIRST") {
            solve_first();
        } else if (phase == "SECOND") {
            solve_second();
        }
    }
    return 0;
}