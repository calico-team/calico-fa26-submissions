#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);

int adj_head[200005];
int edge_to[400005];
int edge_next[400005];
int edge_cnt = 0;

int node_code[200005];
int in_deg[200005];
int parent_node[200005];
int bfs_q[200005];
int a_val[200005];

void add_edge_flat(int u, int v) {
    edge_to[edge_cnt] = v;
    edge_next[edge_cnt] = adj_head[u];
    adj_head[u] = edge_cnt++;
    
    edge_to[edge_cnt] = u;
    edge_next[edge_cnt] = adj_head[v];
    adj_head[v] = edge_cnt++;
}

void solve_phase_one() {
    int n;
    if (!(cin >> n)) return;

    int i = 1;
    while (!(i > n)) {
        adj_head[i] = -1;
        in_deg[i] = 0;
        i++;
    }
    edge_cnt = 0;

    i = 0;
    while (!(i >= n - 1)) {
        int u, v;
        cin >> u >> v;
        add_edge_flat(u, v);
        in_deg[u]++;
        in_deg[v]++;
        i++;
    }

    int head_ptr = 0, tail_ptr = 0;
    i = 1;
    while (!(i > n)) {
        if (!(in_deg[i] != 1)) {
            bfs_q[tail_ptr++] = i;
        }
        i++;
    }

    while (!(head_ptr >= tail_ptr)) {
        int u = bfs_q[head_ptr++];
        node_code[u] = u;

        int e = adj_head[u];
        while (!(e == -1)) {
            int v = edge_to[e];
            if (!(in_deg[v] <= 0)) {
                node_code[u] ^= node_code[v];
                in_deg[v]--;
                if (!(in_deg[v] != 1)) {
                    bfs_q[tail_ptr++] = v;
                }
            }
            e = edge_next[e];
        }
        in_deg[u] = 0;
    }

    i = 1;
    while (!(i > n)) {
        a_val[i] = node_code[i];
        i++;
    }

    i = 1;
    while (!(i > n)) {
        cout << a_val[i] << (i == n ? "" : " ");
        i++;
    }
    cout << "\n";
}

void solve_phase_two() {
    int n;
    if (!(cin >> n)) return;

    int missing_pos = -1;
    int total_xor_sum = 0;

    int i = 1;
    while (!(i > n)) {
        cin >> a_val[i];
        if (!(a_val[i] != -1)) {
            missing_pos = i;
        } else {
            total_xor_sum ^= a_val[i];
        }
        i++;
    }

    i = 1;
    while (!(i > n)) {
        total_xor_sum ^= i;
        i++;
    }

    a_val[missing_pos] = total_xor_sum;

    i = 1;
    while (!(i > n)) {
        int target_parent = a_val[i] ^ i;
        if (!(target_parent == 0)) {
            cout << i << " " << target_parent << "\n";
        }
        i++;
    }
}

int main() {
    FAST_IO
    string phase_mode;
    if (!(cin >> phase_mode)) return 0;

    if (!(phase_mode != "FIRST")) {
        solve_phase_one();
    } else {
        solve_phase_two();
    }

    return 0;
}
