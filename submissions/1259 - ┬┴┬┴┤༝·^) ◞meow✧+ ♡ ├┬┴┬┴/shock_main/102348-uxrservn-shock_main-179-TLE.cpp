#include <bits/stdc++.h>

using namespace std;

#define int long long

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int t;
  cin >> t;
  while (t--) {
    int n, m, q;
    cin >> n >> m >> q;
    int r, c, p;
    vector<vector<int>> earthquakes(q, vector<int>(3));
    for (int i = 0; i < q; ++i) {
      cin >> r >> c >> p;
      earthquakes[i] = {r, c, p};
    }
    bool swapped = false;
    if (n > m) {
      swapped = true;
      swap(n, m);
      for (int i = 0; i < q; ++i) {
        swap(earthquakes[i][0], earthquakes[i][1]);
      }
    }

    vector<vector<int>> grid(n, vector<int>(m, -1));
    for (int i = 0; i < n; ++i) {
      vector<tuple<int, int, int>> affected_columns;
      for (int j = 0; j < q; ++j) {
        int r = earthquakes[j][0];
        int c = earthquakes[j][1];
        int p = earthquakes[j][2];
        // affected if p^2 - ((r - i)^2 + (c - j)^2) + 1 > 0

        // - (c-j)^2 > -p^2 + (r-i)^2 - 1
        // (c-j)^2 < p^2 - (r-i)^2 + 1
        // (c-j)^2 < d
        // c - sqrt(d) < j < c + sqrt(d)
        int d = p * p - (r - i) * (r - i) + 1;
        if (d > 0) {
          int start = max(0LL, (int)ceil(c - sqrt(d) + 1e-9));
          int end = min(m - 1LL, (int)floor(c + sqrt(d) - 1e-9));
          affected_columns.push_back({start, end, j});
        }
      }

      sort(affected_columns.begin(), affected_columns.end());

      priority_queue<pair<int, int>> max_pq;
      int idx = 0;
      for (int j = 0; j < m; ++j) {
        while (idx < affected_columns.size() &&
               get<0>(affected_columns[idx]) <= j) {
          max_pq.push(
              {get<2>(affected_columns[idx]), get<1>(affected_columns[idx])});
          idx++;
        }
        while (!max_pq.empty() && max_pq.top().second < j) {
          max_pq.pop();
        }
        if (!max_pq.empty()) {
          grid[i][j] = max_pq.top().first;
        }
      }
    }

    if (swapped) {
      vector<vector<int>> transposed_grid(m, vector<int>(n, 0));
      for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
          transposed_grid[j][i] = grid[i][j];
        }
      }
      grid = transposed_grid;

      for (int i = 0; i < q; ++i) {
        swap(earthquakes[i][0], earthquakes[i][1]);
      }
    }

    for (int i = 0; i < grid.size(); ++i) {
      for (int j = 0; j < grid[0].size(); ++j) {
        if (grid[i][j] == -1) {
          cout << "0 ";
        } else {
          // cout << "Calculating intensity for cell (" << i << ", " << j << ")"
          //      << endl;
          // cout << "Earthquake number: " << grid[i][j] << endl;
          // cout << "Earthquake details: r = " << earthquakes[grid[i][j]][0]
          //      << ", c = " << earthquakes[grid[i][j]][1]
          //      << ", p = " << earthquakes[grid[i][j]][2] << endl;
          int r = earthquakes[grid[i][j]][0];
          int c = earthquakes[grid[i][j]][1];
          int p = earthquakes[grid[i][j]][2];
          int intensity = p * p - ((r - i) * (r - i) + (c - j) * (c - j)) + 1;
          cout << intensity << " ";
        }
      }
      cout << endl;
    }
  }
}