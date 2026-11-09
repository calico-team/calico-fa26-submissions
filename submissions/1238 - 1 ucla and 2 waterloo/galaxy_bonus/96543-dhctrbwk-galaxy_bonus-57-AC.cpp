#include <bits/stdc++.h>
using namespace std;

struct point {
	int x, y;
	bool operator==(const point &o) const {
		return x == o.x && y == o.y;
	}
};

char grid[256][256];
point dsu[256][256];

void init(int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			dsu[i][j] = {i, j};
		}
	}
}

point root(const point p) {
	auto [x, y] = p;
	if (dsu[x][y] == p)
		return p;

	return dsu[x][y] = root(dsu[x][y]);
}

void join(const point a, const point b) {
	auto [x, y] = root(a);
	dsu[x][y] = root(b);
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

	int t;
	cin >> t;
	while (t--) {
		int n, m, q;
		cin >> n >> m >> q;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> grid[i][j];
			}
		}
		init(n, m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m - 1; j++) {
				if (grid[i][j] == grid[i][j + 1] || grid[i][j] == '.' || grid[i][j + 1] == '.')
					join({i, j}, {i, j + 1});
			}
		}
		for (int i = 0; i < n - 1; i++) {
			for (int j = 0; j < m; j++) {
				if (grid[i][j] == grid[i + 1][j] || grid[i][j] == '.' || grid[i + 1][j] == '.')
					join({i, j}, {i + 1, j});
			}
		}
		while (q--) {
			int a, b, c, d;
			cin >> a >> b >> c >> d;
			if (root({a, b}) == root({c, d}))
				cout << "YES\n";
			else
				cout << "NO\n";
		}
	}

	return 0;
}
