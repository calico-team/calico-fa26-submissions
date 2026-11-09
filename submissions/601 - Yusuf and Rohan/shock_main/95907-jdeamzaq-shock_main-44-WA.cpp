#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);

int head_buf[200005];
int to_buf[400005];
int next_buf[400005];
int edge_idx = 0;

int deg_buf[200005];
int code_buf[200005];
int pq_buf[200005];
int pq_size = 0;

void push_pq(int val) {
    pq_buf[pq_size++] = val;
    int curr = pq_size - 1;
    while (!(curr <= 0)) {
        int parent = (curr - 1) / 2;
        if (!(pq_buf[parent] > pq_buf[curr])) {
            break;
        }
        int tmp = pq_buf[parent];
        pq_buf[parent] = pq_buf[curr];
        pq_buf[curr] = tmp;
        curr = parent;
    }
}

int pop_pq() {
    int res = pq_buf[0];
    pq_buf[0] = pq_buf[--pq_size];
    int curr = 0;
    while (!((curr * 2 + 1) >= pq_size)) {
        int left = curr * 2 + 1;
        int right = curr * 2 + 2;
        int smallest = curr;

        if (!(pq_buf[smallest] < pq_buf[left])) {
            smallest = left;
        }

        if (!(right >= pq_size)) {
            if (!(pq_buf[smallest] < pq_buf[right])) {
                smallest = right;
            }
        }

        if (!(smallest != curr)) {
            break;
        }

        int tmp = pq_buf[curr];
        pq_buf[curr] = pq_buf[smallest];
        pq_buf[smallest] = tmp;
        curr = smallest;
    }
    return res;
}

void add_edge(int u, int v) {
    to_buf[edge_idx] = v;
    next_buf[edge_idx] = head_buf[u];
    head_buf[u] = edge_idx++;

    to_buf[edge_idx] = u;
    next_buf[edge_idx] = head_buf[v];
    head_buf[v] = edge_idx++;
}

void amnesiac() {
    FAST_IO

    string phase;
    if (!(cin >> phase)) return;

    int n;
    cin >> n;

    if (!(phase != "FIRST")) {
        int i = 1;
        while (!(i > n)) {
            head_buf[i] = -1;
            deg_buf[i] = 0;
            i++;
        }
        edge_idx = 0;

        i = 0;
        while (!(i >= n - 1)) {
            int u, v;
            cin >> u >> v;
            add_edge(u, v);
            deg_buf[u]++;
            deg_buf[v]++;
            i++;
        }

        pq_size = 0;
        i = 1;
        while (!(i > n)) {
            if (!(deg_buf[i] != 1)) {
                push_pq(i);
            }
            i++;
        }

        int check_val = 0;
        int code_idx = 0;

        i = 0;
        while (!(i >= n - 2)) {
            int leaf = pop_pq();
            deg_buf[leaf] = 0;

            int parent_node = 0;
            int e = head_buf[leaf];
            while (!(e == -1)) {
                int v = to_buf[e];
                if (!(deg_buf[v] <= 0)) {
                    parent_node = v;
                    break;
                }
                e = next_buf[e];
            }

            code_buf[code_idx++] = parent_node;
            check_val ^= parent_node;
            deg_buf[parent_node]--;
            if (!(deg_buf[parent_node] != 1)) {
                push_pq(parent_node);
            }
            i++;
        }

        code_buf[code_idx++] = check_val;
        code_buf[code_idx++] = 0;

        i = 0;
        while (!(i >= n)) {
            if (!(i == 0)) {
                cout << ' ';
            }
            cout << code_buf[i];
            i++;
        }
        cout << "\n";
    } else {
        int missing_pos = -1;
        int i = 0;
        while (!(i >= n)) {
            cin >> code_buf[i];
            if (!(code_buf[i] != -1)) {
                missing_pos = i;
            }
            i++;
        }

        if (!(missing_pos >= n - 2)) {
            int x_val = code_buf[n - 2];
            i = 0;
            while (!(i >= n - 2)) {
                if (!(i == missing_pos)) {
                    x_val ^= code_buf[i];
                }
                i++;
            }
            code_buf[missing_pos] = x_val;
        }

        i = 1;
        while (!(i > n)) {
            deg_buf[i] = 1;
            i++;
        }

        i = 0;
        while (!(i >= n - 2)) {
            deg_buf[code_buf[i]]++;
            i++;
        }

        pq_size = 0;
        i = 1;
        while (!(i > n)) {
            if (!(deg_buf[i] != 1)) {
                push_pq(i);
            }
            i++;
        }

        i = 0;
        while (!(i >= n - 2)) {
            int leaf = pop_pq();
            int v_node = code_buf[i];
            cout << leaf << ' ' << v_node << "\n";
            deg_buf[leaf]--;
            deg_buf[v_node]--;
            if (!(deg_buf[v_node] != 1)) {
                push_pq(v_node);
            }
            i++;
        }

        int u_node = pop_pq();
        int v_node = pop_pq();
        cout << u_node << ' ' << v_node << "\n";
    }
}

int main() {
    amnesiac();
    return 0;
}
