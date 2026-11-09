#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

const long long INF = 1e15;

struct Query {
  int r2, c2, K, idx;
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

  vector<vector<Query>> queries_by_start(N * M);
  vector<long long> ans_dist(Q, INF);
  vector<long long> query_K(Q);

  for (int i = 0; i < Q; ++i) {
    int r1, c1, r2, c2, K;
    cin >> r1 >> c1 >> r2 >> c2 >> K;
    queries_by_start[r1 * M + c1].push_back({r2, c2, K, i});
    query_K[i] = K;
  }

  int S = N * M * 2;
  vector<int> dist_array(S, -1);

  int dr[] = {-1, 1, 0, 0};
  int dc[] = {0, 0, -1, 1};

  for (int s_cell = 0; s_cell < N * M; ++s_cell) {
    if (queries_by_start[s_cell].empty())
      continue;

    int start_state = s_cell * 2;

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

    for (const auto &target : queries_by_start[s_cell]) {
      int t_cell = target.r2 * M + target.c2;
      int t_0 = t_cell * 2;
      int t_1 = t_0 + 1;

      long long min_d = INF;
      if (dist_array[t_0] != -1)
        min_d = min(min_d, (long long)dist_array[t_0]);
      if (dist_array[t_1] != -1)
        min_d = min(min_d, (long long)dist_array[t_1]);
      ans_dist[target.idx] = min_d;
    }

    for (int node : visited_nodes) {
      dist_array[node] = -1;
    }
  }

  for (int i = 0; i < Q; ++i) {
    if (ans_dist[i] <= query_K[i]) {
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
