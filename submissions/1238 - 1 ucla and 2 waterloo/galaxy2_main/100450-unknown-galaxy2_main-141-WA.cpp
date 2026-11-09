#include <bits/stdc++.h>
using namespace std;

enum Color {
	Blue,
	Red,
};

Color opp(Color c) {
	return c == Blue ? Red : Blue;
}

struct ent {
	int w, x, y;
	Color col;
	bool operator<(const ent &o) const {
		return w > o.w;
	}
};

char grid[16][4096];
int gen[16][4096];
vector<pair<int, int>> adj[16][4096];

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int t;
	cin >> t;
	while (t--) {
		memset(gen, -1, sizeof(gen));

		int n, m, q;
		cin >> n >> m >> q;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> grid[i][j];
				if (grid[i][j] == 'B')
					grid[i][j] = Blue;
				if (grid[i][j] == 'R')
					grid[i][j] = Red;
				adj[i][j].clear();
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m - 1; j++) {
				if (grid[i][j] == grid[i][j + 1] || grid[i][j] == '.' || grid[i][j + 1] == '.') {
					adj[i][j].emplace_back(i, j + 1);
					adj[i][j + 1].emplace_back(i, j);
				}
			}
		}
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < m; j++) {
				if (grid[i][j] == grid[i + 1][j] || grid[i][j] == '.' || grid[i + 1][j] == '.') {
					adj[i][j].emplace_back(i + 1, j);
					adj[i + 1][j].emplace_back(i, j);
				}
			}
		}

		priority_queue<ent> pq;
		for (int g = 0; g < q; g++) {
			int a, b, c, d, k;
			cin >> a >> b >> c >> d >> k;
			pq.push({0, a, b, Blue});
			while (!pq.empty()) {
				auto [w, x, y, col] = pq.top();
				pq.pop();
				if (gen[x][y] == g)
					continue;
				gen[x][y] = g;
				if (x == c && y == d) {
					if (w > k)
						cout << "NO\n";
					else
						cout << "YES\n";
					goto done;
				}
				if (w > k)
					continue;
				for (auto [nx, ny] : adj[x][y]) {
					if (grid[nx][ny] != '.' && grid[nx][ny] != col)
						pq.push({w + 2, nx, ny, opp(col)});
					else
						pq.push({w + 1, nx, ny, col});
				}
			}
			cout << "NO\n";
		done:;
		}
	}

	return 0;
}
