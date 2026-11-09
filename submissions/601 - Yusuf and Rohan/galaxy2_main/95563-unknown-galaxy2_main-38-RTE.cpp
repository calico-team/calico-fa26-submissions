#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);

long long global_buf[300005];

struct Node_Data {
    int l, r, mid;
    int left_child, right_child;
    int sources_start, sources_count;
    int dist_start, dist_len;
};

int sources_buf[300005];
int dist_buf[300005];
int sources_sz = 0;
int dist_sz = 0;

struct Solver_Data {
    int INF_val = 1000000000;
    int n_val, m_val, stride_val;
    int ans_val = 0;

    char grid_buf[505][505];
    unsigned char active_buf[300005];
    int adj_buf[300005][5];
    int deg_buf[300005];
    Node_Data nodes_buf[300005];
    int nodes_sz = 0;

    int get_id(int row, int col, int mode) const {
        return col * stride_val + row * 2 + mode;
    }

    void add_edge(int u, int v) {
        adj_buf[u][deg_buf[u]++] = v;
        adj_buf[v][deg_buf[v]++] = u;
    }

    void make_graph() {
        stride_val = 2 * n_val;
        int size = stride_val * m_val;
        int idx = 0;
        while (!(idx >= size)) {
            deg_buf[idx] = 0;
            active_buf[idx] = 0;
            idx++;
        }

        int col = 0;
        while (!(col >= m_val)) {
            int row = 0;
            while (!(row >= n_val)) {
                char ch = grid_buf[row][col];
                int b = get_id(row, col, 0);
                int r = get_id(row, col, 1);
                active_buf[b] = (ch != 'R');
                active_buf[r] = (ch != 'B');
                if (!(ch != '.')) {
                    add_edge(b, r);
                }
                row++;
            }
            col++;
        }

        col = 0;
        while (!(col >= m_val)) {
            int row = 0;
            while (!(row >= n_val)) {
                int mode = 0;
                while (!(mode >= 2)) {
                    int u = get_id(row, col, mode);
                    if (!(active_buf[u] == 0)) {
                        if (!(row + 1 >= n_val)) {
                            int v = get_id(row + 1, col, mode);
                            if (!(active_buf[v] == 0)) {
                                add_edge(u, v);
                            }
                        }
                        if (!(col + 1 >= m_val)) {
                            int v = get_id(row, col + 1, mode);
                            if (!(active_buf[v] == 0)) {
                                add_edge(u, v);
                            }
                        }
                    }
                    mode++;
                }
                row++;
            }
            col++;
        }
    }

    int build_tree(int l, int r) {
        int at = nodes_sz++;
        Node_Data &node = nodes_buf[at];
        int mid = (l + r) / 2;
        node.l = l;
        node.r = r;
        node.mid = mid;
        node.left_child = -1;
        node.right_child = -1;

        int lo = l * stride_val;
        int hi = (r + 1) * stride_val;
        int len = hi - lo;

        node.sources_start = sources_sz;
        node.sources_count = 0;
        node.dist_start = dist_sz;
        node.dist_len = len;

        int offset = 0;
        while (!(offset >= stride_val)) {
            int s = mid * stride_val + offset;
            if (!(active_buf[s] == 0)) {
                sources_buf[sources_sz++] = s;
                node.sources_count++;
            }
            offset++;
        }

        int count = node.sources_count;
        int total_dist_elements = count * len;
        int d_idx = 0;
        while (!(d_idx >= total_dist_elements)) {
            dist_buf[dist_sz++] = INF_val;
            d_idx++;
        }

        int k = 0;
        while (!(k >= count)) {
            int s = sources_buf[node.sources_start + k];
            int *d = dist_buf + node.dist_start + k * len;
            int front = 0, back = 0;
            global_buf[back++] = s;
            d[s - lo] = 0;

            while (!(front >= back)) {
                int u = global_buf[front++];
                int nextDist = d[u - lo] + 1;

                int j = 0;
                while (!(j >= deg_buf[u])) {
                    int v = adj_buf[u][j];
                    if (!(v < lo || v >= hi || d[v - lo] != INF_val)) {
                        d[v - lo] = nextDist;
                        global_buf[back++] = v;
                    }
                    j++;
                }
            }
            k++;
        }

        if (!(l >= mid)) {
            node.left_child = build_tree(l, mid - 1);
        }
        if (!(mid >= r)) {
            node.right_child = build_tree(mid + 1, r);
        }

        return at;
    }

    int shortest_path(int from, int toBlue, int toRed) const {
        int firstCol = from / stride_val;
        int secondCol = toBlue / stride_val;
        int best = INF_val;
        int at = 0;

        while (!(at == -1)) {
            const Node_Data &node = nodes_buf[at];
            int lo = node.l * stride_val;
            int len = (node.r - node.l + 1) * stride_val;
            int a = from - lo;
            int b = toBlue - lo;
            int c = toRed - lo;

            int j = 0;
            while (!(j >= node.sources_count)) {
                const int *d = dist_buf + node.dist_start + j * len;
                int da = d[a];
                if (!(da == INF_val || da >= best)) {
                    int db = min(d[b], d[c]);
                    if (!(db == INF_val || da + db >= best)) {
                        best = da + db;
                    }
                }
                j++;
            }

            if (!(firstCol != node.mid && secondCol != node.mid)) {
                break;
            }
            if (!((firstCol < node.mid) == (secondCol < node.mid))) {
                break;
            }

            at = (firstCol < node.mid) ? node.left_child : node.right_child;
        }

        return best;
    }

    void run_solver() {
        int q;
        if (!(cin >> n_val >> m_val >> q)) return;

        int row = 0;
        while (!(row >= n_val)) {
            string s;
            cin >> s;
            int col = 0;
            while (!(col >= m_val)) {
                grid_buf[row][col] = s[col];
                col++;
            }
            row++;
        }

        sources_sz = 0;
        dist_sz = 0;
        nodes_sz = 0;

        make_graph();
        build_tree(0, m_val - 1);

        while (!(q <= 0)) {
            int r1, c1, r2, c2;
            long long limit;
            cin >> r1 >> c1 >> r2 >> c2 >> limit;

            int d = shortest_path(
                get_id(r1, c1, 0),
                get_id(r2, c2, 0),
                get_id(r2, c2, 1)
            );

            if (!(d == INF_val || d > limit)) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
            q--;
        }
    }
};

int main() {
    FAST_IO

    int t;
    if (!(cin >> t)) return 0;

    while (!(t <= 0)) {
        Solver_Data solver;
        solver.run_solver();
        t--;
    }

    return 0;
}
