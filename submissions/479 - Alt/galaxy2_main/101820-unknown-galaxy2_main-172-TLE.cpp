#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

const long long INF = 1e15;

struct Query {
  int r1, c1, r2, c2, K, idx;
};

int dist_array[80005];
int visited_nodes[80005];
int mid_dists[22][80005];

void solve() {
  int N, M, Q;
  if (!(cin >> N >> M >> Q))
    return;

  vector<string> grid(N);
  for (int r = 0; r < N; ++r) {
    cin >> grid[r];
  }

  vector<int> grid_mask(N * M, 0);
  for (int r = 0; r < N; ++r) {
    for (int c = 0; c < M; ++c) {
      char ch = grid[r][c];
      if (ch == '.')
        grid_mask[r * M + c] = 3;
      else if (ch == 'R')
        grid_mask[r * M + c] = 2;
      else if (ch == 'B')
        grid_mask[r * M + c] = 1;
    }
  }

  vector<Query> queries(Q);
  for (int i = 0; i < Q; ++i) {
    cin >> queries[i].r1 >> queries[i].c1 >> queries[i].r2 >> queries[i].c2 >>
        queries[i].K;
    queries[i].idx = i;
  }

  vector<long long> ans_dist(Q, INF);
  int S = N * M * 2;

  fill(dist_array, dist_array + S, -1);

  int dr[] = {-1, 1, 0, 0};
  int dc[] = {0, 0, -1, 1};

  auto dandq = [&](auto &self, int L, int R,
                   const vector<Query> &curr_queries) -> void {
    if (L > R || curr_queries.empty())
      return;

    int mid = L + (R - L) / 2;

    vector<Query> mid_queries, next_left, next_right;
    mid_queries.reserve(curr_queries.size());

    for (const auto &q : curr_queries) {
      int min_c = min(q.c1, q.c2);
      int max_c = max(q.c1, q.c2);
      if (min_c <= mid && mid <= max_c) {
        mid_queries.push_back(q);
      } else if (max_c < mid) {
        next_left.push_back(q);
      } else {
        next_right.push_back(q);
      }
    }

    if (!mid_queries.empty()) {
      int mid_state_count = 2 * N;

      for (int i = 0; i < mid_state_count; ++i) {
        int r_mid = i / 2;
        int m_mid = i % 2;
        int cell = r_mid * M + mid;
        int mask = grid_mask[cell];

        if ((m_mid == 0 && !(mask & 1)) || (m_mid == 1 && !(mask & 2))) {
          fill(mid_dists[i], mid_dists[i] + S, -1);
          continue;
        }

        int start_state = cell * 2 + m_mid;

        queue<int> q;
        q.push(start_state);
        dist_array[start_state] = 0;

        int v_head = 0;
        visited_nodes[v_head++] = start_state;

        while (!q.empty()) {
          int u = q.front();
          q.pop();
          int d = dist_array[u];

          int curr_m = u % 2;
          int c_cell = u / 2;
          int curr_c = c_cell % M;
          int curr_r = c_cell / M;

          if (grid_mask[c_cell] == 3) {
            int nxt = u ^ 1;
            if (dist_array[nxt] == -1) {
              dist_array[nxt] = d + 1;
              q.push(nxt);
              visited_nodes[v_head++] = nxt;
            }
          }

          for (int dir = 0; dir < 4; ++dir) {
            int nr = curr_r + dr[dir];
            int nc = curr_c + dc[dir];
            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
              int nxt_cell = nr * M + nc;
              int n_mask = grid_mask[nxt_cell];
              if ((curr_m == 0 && (n_mask & 1)) ||
                  (curr_m == 1 && (n_mask & 2))) {
                int nxt = nxt_cell * 2 + curr_m;
                if (dist_array[nxt] == -1) {
                  dist_array[nxt] = d + 1;
                  q.push(nxt);
                  visited_nodes[v_head++] = nxt;
                }
              }
            }
          }
        }

        fill(mid_dists[i], mid_dists[i] + S, -1);
        for (int k = 0; k < v_head; ++k) {
          int node = visited_nodes[k];
          mid_dists[i][node] = dist_array[node];
        }

        for (int k = 0; k < v_head; ++k) {
          dist_array[visited_nodes[k]] = -1;
        }
      }

      for (const auto &q : mid_queries) {
        int s_cell = q.r1 * M + q.c1;
        int t_cell = q.r2 * M + q.c2;

        int s_blue = s_cell * 2;
        int s_red = s_blue + 1;
        int t_blue = t_cell * 2;
        int t_red = t_blue + 1;

        long long min_d = INF;
        for (int i = 0; i < mid_state_count; ++i) {
          int d1_b = mid_dists[i][s_blue];
          if (d1_b != -1) {
            int d2_0 = mid_dists[i][t_blue];
            int d2_1 = mid_dists[i][t_red];
            if (d2_0 != -1 && (long long)d1_b + d2_0 < min_d)
              min_d = (long long)d1_b + d2_0;
            if (d2_1 != -1 && (long long)d1_b + d2_1 < min_d)
              min_d = (long long)d1_b + d2_1;
          }

          int d1_r = mid_dists[i][s_red];
          if (d1_r != -1) {
            int d2_0 = mid_dists[i][t_blue];
            int d2_1 = mid_dists[i][t_red];
            if (d2_0 != -1 && (long long)d1_r + d2_0 + 1 < min_d)
              min_d = (long long)d1_r + d2_0 + 1;
            if (d2_1 != -1 && (long long)d1_r + d2_1 + 1 < min_d)
              min_d = (long long)d1_r + d2_1 + 1;
          }
        }
        ans_dist[q.idx] = min_d;
      }
    }

    self(self, L, mid - 1, next_left);
    self(self, mid + 1, R, next_right);
  };

  dandq(dandq, 0, M - 1, queries);

  for (int i = 0; i < Q; ++i) {
    if (ans_dist[i] <= queries[i].K) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  if (cin >> T) {
    while (T--) {
      solve();
    }
  }
  return 0;
}
