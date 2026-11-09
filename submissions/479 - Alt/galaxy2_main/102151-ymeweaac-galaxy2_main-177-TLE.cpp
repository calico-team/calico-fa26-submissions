#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

const long long INF = 1e15;

struct Query {
    int r1, c1, r2, c2, K, idx;
};

inline int next_int() {
    int c = getchar();
    while (c <= 32) {
        if (c == EOF) return 0;
        c = getchar();
    }
    int res = 0;
    while (c > 32) {
        res = res * 10 + (c - '0');
        c = getchar();
    }
    return res;
}

inline string next_string() {
    int c = getchar();
    while (c <= 32) {
        if (c == EOF) return "";
        c = getchar();
    }
    string res = "";
    while (c > 32) {
        res += (char)c;
        c = getchar();
    }
    return res;
}

int dist_array[200005];
int visited_nodes[200005];
int q_buffer[200005]; 
int grid_mask[200005];

Query queries[200005];
int query_indices[200005];
int temp_indices[200005];
long long ans_dist[200005];

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};
int N, M, Q;

void dandq(int L, int R, int q_start, int q_end) {
    if (L > R || q_start >= q_end) return;

    int mid = L + (R - L) / 2;

    int mid_start = q_start;
    int left_ptr = q_start;
    int right_ptr = q_end;

    for (int i = q_start; i < q_end; ++i) {
        int q_idx = query_indices[i];
        int min_c = min(queries[q_idx].c1, queries[q_idx].c2);
        int max_c = max(queries[q_idx].c1, queries[q_idx].c2);

        if (min_c <= mid && mid <= max_c) {
            temp_indices[mid_start++] = q_idx;
        }
    }

    int left_start = mid_start;
    for (int i = q_start; i < q_end; ++i) {
        int q_idx = query_indices[i];
        int min_c = min(queries[q_idx].c1, queries[q_idx].c2);
        int max_c = max(queries[q_idx].c1, queries[q_idx].c2);

        if (!(min_c <= mid && mid <= max_c)) {
            if (max_c < mid) {
                temp_indices[mid_start++] = q_idx;
            }
        }
    }

    int right_start = mid_start;
    for (int i = q_start; i < q_end; ++i) {
        int q_idx = query_indices[i];
        int min_c = min(queries[q_idx].c1, queries[q_idx].c2);
        int max_c = max(queries[q_idx].c1, queries[q_idx].c2);

        if (!(min_c <= mid && mid <= max_c)) {
            if (!(max_c < mid)) {
                temp_indices[mid_start++] = q_idx;
            }
        }
    }

    for (int i = q_start; i < q_end; ++i) {
        query_indices[i] = temp_indices[i];
    }

    int mid_count = left_start - q_start;

    if (mid_count > 0) {
        int mid_state_count = 2 * N;
        for (int i = 0; i < mid_state_count; ++i) {
            int r_mid = i / 2;
            int m_mid = i % 2;
            int cell = r_mid * M + mid;
            int mask = grid_mask[cell];
            
            if ((m_mid == 0 && !(mask & 1)) || (m_mid == 1 && !(mask & 2))) {
                continue;
            }

            int start_state = cell * 2 + m_mid;
            
            int q_head = 0, q_tail = 0;
            q_buffer[q_tail++] = start_state;
            dist_array[start_state] = 0;

            int v_head = 0;
            visited_nodes[v_head++] = start_state;

            while (q_head < q_tail) {
                int u = q_buffer[q_head++];
                int d = dist_array[u];
                int curr_m = u % 2;
                int c_cell = u / 2;
                int curr_c = c_cell % M;
                int curr_r = c_cell / M;

                if (grid_mask[c_cell] == 3) {
                    int nxt = u ^ 1;
                    if (dist_array[nxt] == -1) {
                        dist_array[nxt] = d + 1;
                        q_buffer[q_tail++] = nxt;
                        visited_nodes[v_head++] = nxt;
                    }
                }

                for (int dir = 0; dir < 4; ++dir) {
                    int nr = curr_r + dr[dir];
                    int nc = curr_c + dc[dir];
                    if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                        int nxt_cell = nr * M + nc;
                        int n_mask = grid_mask[nxt_cell];
                        if ((curr_m == 0 && (n_mask & 1)) || (curr_m == 1 && (n_mask & 2))) {
                            int nxt = nxt_cell * 2 + curr_m;
                            if (dist_array[nxt] == -1) {
                                dist_array[nxt] = d + 1;
                                q_buffer[q_tail++] = nxt;
                                visited_nodes[v_head++] = nxt;
                            }
                        }
                    }
                }
            }

            for (int k = q_start; k < left_start; ++k) {
                int q_idx = query_indices[k];
                int s_cell = queries[q_idx].r1 * M + queries[q_idx].c1;
                int t_cell = queries[q_idx].r2 * M + queries[q_idx].c2;
                int s_blue = s_cell * 2;
                int s_red = s_blue + 1;
                int t_blue = t_cell * 2;
                int t_red = t_blue + 1;

                int d1_b = dist_array[s_blue];
                int d1_r = dist_array[s_red];
                int d2_b = dist_array[t_blue];
                int d2_r = dist_array[t_red];

                if (d1_b != -1) {
                    if (d2_b != -1) ans_dist[q_idx] = min(ans_dist[q_idx], (long long)d1_b + d2_b);
                    if (d2_r != -1) ans_dist[q_idx] = min(ans_dist[q_idx], (long long)d1_b + d2_r);
                }
                if (d1_r != -1) {
                    if (d2_b != -1) ans_dist[q_idx] = min(ans_dist[q_idx], (long long)d1_r + d2_b + 1);
                    if (d2_r != -1) ans_dist[q_idx] = min(ans_dist[q_idx], (long long)d1_r + d2_r + 1);
                }
            }

            for (int k = 0; k < v_head; ++k) {
                dist_array[visited_nodes[k]] = -1;
            }
        }
    }

    dandq(L, mid - 1, left_start, right_start);
    dandq(mid + 1, R, right_start, q_end);
}

void solve() {
    N = next_int();
    if (N == 0) return;
    M = next_int();
    Q = next_int();

    for (int r = 0; r < N; ++r) {
        string s = next_string();
        for (int c = 0; c < M; ++c) {
            char ch = s[c];
            if (ch == '.') grid_mask[r * M + c] = 3;
            else if (ch == 'R') grid_mask[r * M + c] = 2;
            else if (ch == 'B') grid_mask[r * M + c] = 1;
            else grid_mask[r * M + c] = 0;
        }
    }

    for (int i = 0; i < Q; ++i) {
        queries[i].r1 = next_int();
        queries[i].c1 = next_int();
        queries[i].r2 = next_int();
        queries[i].c2 = next_int();
        queries[i].K = next_int();
        queries[i].idx = i;
        query_indices[i] = i;
        ans_dist[i] = INF;
    }

    int S = N * M * 2;
    fill(dist_array, dist_array + S, -1);

    dandq(0, M - 1, 0, Q);

    for (int i = 0; i < Q; ++i) {
        if (ans_dist[i] <= queries[i].K) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}

int main() {
    int T = next_int();
    while (T--) {
        solve();
    }
    return 0;
}
