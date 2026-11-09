#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);

const int INF = 1e9;

int N, M, Q;
char grid[12][4005];

struct Query {
    int r1, c1, r2, c2, k, id;
};

bool ans_arr[100005];
int dist_buf[20][11][4005][2];
int q_r[80005], q_c[80005], q_m[80005];

bool is_active(char ch, int mode) {
    if (ch == '.') return true;
    if (mode == 0 && ch == 'B') return true;
    if (mode == 1 && ch == 'R') return true;
    return false;
}

void solve_dc(int L, int R, const vector<Query>& queries) {
    if (L > R || queries.empty()) return;
    int mid = (L + R) / 2;

    int num_mid_states = 0;
    int mid_r[20], mid_m[20];

    for (int r = 0; r < N; r++) {
        for (int m = 0; m < 2; m++) {
            if (is_active(grid[r][mid], m)) {
                mid_r[num_mid_states] = r;
                mid_m[num_mid_states] = m;
                num_mid_states++;
            }
        }
    }

    for (int s = 0; s < num_mid_states; s++) {
        for (int r = 0; r < N; r++) {
            for (int c = L; c <= R; c++) {
                dist_buf[s][r][c][0] = INF;
                dist_buf[s][r][c][1] = INF;
            }
        }

        int head = 0, tail = 0;
        int sr = mid_r[s], sm = mid_m[s];
        dist_buf[s][sr][mid][sm] = 0;
        q_r[tail] = sr; q_c[tail] = mid; q_m[tail] = sm; tail++;

        while (head < tail) {
            int cr = q_r[head], cc = q_c[head], cm = q_m[head];
            head++;
            int d = dist_buf[s][cr][cc][cm];

            if (grid[cr][cc] == '.') {
                int nm = 1 - cm;
                if (dist_buf[s][cr][cc][nm] == INF) {
                    dist_buf[s][cr][cc][nm] = d + 1;
                    q_r[tail] = cr; q_c[tail] = cc; q_m[tail] = nm; tail++;
                }
            }

            static int dr[] = {-1, 1, 0, 0};
            static int dc[] = {0, 0, -1, 1};
            for (int i = 0; i < 4; i++) {
                int nr = cr + dr[i];
                int nc = cc + dc[i];
                if (nr >= 0 && nr < N && nc >= L && nc <= R) {
                    if (is_active(grid[nr][nc], cm)) {
                        if (dist_buf[s][nr][nc][cm] == INF) {
                            dist_buf[s][nr][nc][cm] = d + 1;
                            q_r[tail] = nr; q_c[tail] = nc; q_m[tail] = cm; tail++;
                        }
                    }
                }
            }
        }
    }

    vector<Query> left_q, right_q;

    for (const auto& q : queries) {
        int min_c = min(q.c1, q.c2);
        int max_c = max(q.c1, q.c2);

        if (min_c <= mid && max_c >= mid) {
            int min_d = INF;
            for (int s = 0; s < num_mid_states; s++) {
                int d1 = dist_buf[s][q.r1][q.c1][0];
                if (d1 == INF) continue;

                for (int m2 = 0; m2 < 2; m2++) {
                    int d2 = dist_buf[s][q.r2][q.c2][m2];
                    if (d2 != INF) {
                        int tot = d1 + d2;
                        if (tot <= q.k && (q.k - tot) % 2 == 0) {
                            min_d = min(min_d, tot);
                        }
                    }
                }
            }
            ans_arr[q.id] = (min_d <= q.k);
        } else if (max_c < mid) {
            left_q.push_back(q);
        } else {
            right_q.push_back(q);
        }
    }

    solve_dc(L, mid - 1, left_q);
    solve_dc(mid + 1, R, right_q);
}

void solve_test() {
    if (!(cin >> N >> M >> Q)) return;
    for (int i = 0; i < N; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < M; j++) grid[i][j] = s[j];
    }

    vector<Query> queries(Q);
    for (int i = 0; i < Q; i++) {
        cin >> queries[i].r1 >> queries[i].c1 >> queries[i].r2 >> queries[i].c2 >> queries[i].k;
        queries[i].id = i;
    }

    solve_dc(0, M - 1, queries);

    for (int i = 0; i < Q; i++) {
        if (ans_arr[i]) cout << "YES\n";
        else cout << "NO\n";
    }
}

int main() {
    FAST_IO
    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        solve_test();
    }
    return 0;
}
