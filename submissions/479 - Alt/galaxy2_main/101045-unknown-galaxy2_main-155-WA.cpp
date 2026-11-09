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
  vector<int> dist_array(S, -1);

  vector<vector<int>> local_mid_dists(25, vector<int>(S, -1));

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
        int start_state = (r_mid * M + mid) * 2 + m_mid;

        queue<int> q;
        q.push(start_state);
        dist_array[start_state] = 0;
        vector<int> visited_nodes;
        visited_nodes.reserve(S);
        visited_nodes.push_back(start_state);

        while (!q.empty()) {
          int u = q.front();
          q.pop();
          int d = dist_array[u];

          int curr_m = u % 2;
          int cell = u / 2;
          int curr_c = cell % M;
          int curr_r = cell / M;

          if (grid_mask[cell] == 3) {
            int nxt = u ^ 1;
            if (dist_array[nxt] == -1) {
              dist_array[nxt] = d + 1;
              q.push(nxt);
              visited_nodes.push_back(nxt);
            }
          }

          for (int dir = 0; dir < 4; ++dir) {
            int nr = curr_r + dr[dir];
            int nc = curr_c + dc[dir];
            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
              int nxt_cell = nr * M + nc;
              int mask = grid_mask[nxt_cell];
              if ((curr_m == 0 && (mask & 1)) || (curr_m == 1 && (mask & 2))) {
                int nxt = nxt_cell * 2 + curr_m;
                if (dist_array[nxt] == -1) {
                  dist_array[nxt] = d + 1;
                  q.push(nxt);
                  visited_nodes.push_back(nxt);
                }
              }
            }
          }
        }

        for (int node = 0; node < S; ++node) {
          local_mid_dists[i][node] = dist_array[node];
        }

        for (int node : visited_nodes) {
          dist_array[node] = -1;
        }
      }

      for (const auto &q : mid_queries) {
        int s_state = (q.r1 * M + q.c1) * 2;
        int t_0 = (q.r2 * M + q.c2) * 2;
        int t_1 = t_0 + 1;

        long long min_d = INF;
        for (int i = 0; i < mid_state_count; ++i) {
          int d1 = local_mid_dists[i][s_state];
          if (d1 != -1) {
            int d2_0 = local_mid_dists[i][t_0];
            int d2_1 = local_mid_dists[i][t_1];
            if (d2_0 != -1 && (long long)d1 + d2_0 < min_d)
              min_d = (long long)d1 + d2_0;
            if (d2_1 != -1 && (long long)d1 + d2_1 < min_d)
              min_d = (long long)d1 + d2_1;
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
