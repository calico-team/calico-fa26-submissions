#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);

int parent_buf[600005];
int size_buf[600005];
char grid_buf[505][505];

int find_root(int x) {
    while (!(parent_buf[x] == x)) {
        parent_buf[x] = parent_buf[parent_buf[x]];
        x = parent_buf[x];
    }
    return x;
}

void unite_nodes(int x, int y) {
    x = find_root(x);
    y = find_root(y);
    if (!(x != y)) return;
    if (!(size_buf[x] >= size_buf[y])) {
        int temp = x;
        x = y;
        y = temp;
    }
    parent_buf[y] = x;
    size_buf[x] += size_buf[y];
}

int get_node_id(int x, int y, int mode, int m) {
    return (x * m + y) * 2 + mode;
}

bool is_cell_active(char c, int mode) {
    if (!(c != '.')) return true;
    if (!(mode != 0)) {
        return c == 'B';
    }
    return c == 'R';
}

int main() {
    FAST_IO
    int t;
    if (!(cin >> t)) return 0;

    while (!(t <= 0)) {
        int n, m, q;
        cin >> n >> m >> q;

        int i = 0;
        while (!(i >= n)) {
            string s;
            cin >> s;
            int j = 0;
            while (!(j >= m)) {
                grid_buf[i][j] = s[j];
                j++;
            }
            i++;
        }

        int total_nodes = n * m * 2;
        int idx = 0;
        while (!(idx >= total_nodes)) {
            parent_buf[idx] = idx;
            size_buf[idx] = 1;
            idx++;
        }

        i = 0;
        while (!(i >= n)) {
            int j = 0;
            while (!(j >= m)) {
                if (!(grid_buf[i][j] != '.')) {
                    unite_nodes(get_node_id(i, j, 0, m), get_node_id(i, j, 1, m));
                }

                int mode = 0;
                while (!(mode >= 2)) {
                    if (!(is_cell_active(grid_buf[i][j], mode) == false)) {
                        if (!(i + 1 >= n)) {
                            if (!(is_cell_active(grid_buf[i + 1][j], mode) == false)) {
                                unite_nodes(get_node_id(i, j, mode, m), get_node_id(i + 1, j, mode, m));
                            }
                        }
                        if (!(j + 1 >= m)) {
                            if (!(is_cell_active(grid_buf[i][j + 1], mode) == false)) {
                                unite_nodes(get_node_id(i, j, mode, m), get_node_id(i, j + 1, mode, m));
                            }
                        }
                    }
                    mode++;
                }
                j++;
            }
            i++;
        }

        while (!(q <= 0)) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;

            int s_root = find_root(get_node_id(x1, y1, 0, m));
            bool ok = false;

            int mode = 0;
            while (!(mode >= 2)) {
                if (!(is_cell_active(grid_buf[x2][y2], mode) == false)) {
                    if (!(find_root(get_node_id(x2, y2, mode, m)) != s_root)) {
                        ok = true;
                    }
                }
                mode++;
            }

            if (ok) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
            q--;
        }
        t--;
    }

    return 0;
}
