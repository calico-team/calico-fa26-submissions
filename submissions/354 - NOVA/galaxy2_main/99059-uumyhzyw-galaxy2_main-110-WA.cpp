#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll INF = 1e18;

// matrix stuff
struct Mat {
	int s;
	vector<vector<ll>> a;
	Mat(int sz = 0) : s(sz), a(sz, vector<ll>(sz, INF)) {
		for (int i = 0; i < sz; ++i) a[i][i] = 0;
	}
};

Mat mul(const Mat& x, const Mat& y) {
	int sz = x.s;
	Mat z(sz);
	for (int i = 0; i < sz; ++i) {
		for (int k = 0; k < sz; ++k) {
			if (x.a[i][k] == INF) continue;
			for (int j = 0; j < sz; ++j) {
				if (y.a[k][j] == INF) continue;
				z.a[i][j] = min(z.a[i][j], x.a[i][k] + y.a[k][j]);
			}
		}
	}
	return z;
}

void solve() {
	int n, m, q;
	if (!(cin >> n >> m >> q)) return;

	vector<string> g(n);
	for (int i = 0; i < n; ++i) cin >> g[i];

	auto ok = [&](int r, int c, int md) {
		char ch = g[r][c];
		if (ch == '.') return true;
		return (ch == 'B') == (md == 0);
	};

	int sz = 2 * n;
	vector<Mat> tree(4 * m);

	// TODO: clean up this segment tree build logic later
	function<void(int, int, int, int)> buildTree = [&](int node, int l, int r, int dummy_param) {
		if (l == r) {
			Mat d(sz);
			for (int i = 0; i < sz; ++i) {
				for (int j = 0; j < sz; ++j) d.a[i][j] = INF;
				d.a[i][i] = 0;
			}

			for (int i = 0; i < sz; ++i) {
				priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
				vector<ll> dist(sz, INF);
				dist[i] = 0;
				pq.push({0, i});

				while (!pq.empty()) {
					auto [d_val, u] = pq.top();
					pq.pop();
					if (d_val > dist[u]) continue;

					int ur = u / 2, um = u % 2;
					if (g[ur][l] == '.' && dist[u ^ 1] > dist[u] + 1) {
						dist[u ^ 1] = dist[u] + 1;
						pq.push({dist[u ^ 1], u ^ 1});
					}

					int dr[] = {1, -1, 0, 0};
					int dc[] = {0, 0, 1, -1};
					for (int d_idx = 0; d_idx < 4; ++d_idx) {
						int nr = ur + dr[d_idx];
						int nc = l + dc[d_idx];
						if (nc == l && nr >= 0 && nr < n && ok(nr, l, um)) {
							int v = nr * 2 + um;
							if (dist[v] > dist[u] + 1) {
								dist[v] = dist[u] + 1;
								pq.push({dist[v], v});
							}
						}
					}
				}
				for (int j = 0; j < sz; ++j) d.a[i][j] = dist[j];
			}

			if (l < m - 1) {
				Mat trans(sz);
				for (int i = 0; i < sz; ++i) {
					for (int j = 0; j < sz; ++j) trans.a[i][j] = INF;
				}
				for (int u = 0; u < sz; ++u) {
					int ur = u / 2, um = u % 2;
					for (int w = 0; w < sz; ++w) {
						int wr = w / 2, wm = w % 2;
						if (wr == ur && wm == um && ok(ur, l, um) && ok(ur, l + 1, um)) {
							for (int v = 0; v < sz; ++v) {
								trans.a[u][v] = min(trans.a[u][v], d.a[u][w] + 1);
							}
						}
					}
				}
				tree[node] = trans;
			} else {
				tree[node] = d;
			}
			return;
		}

		int mid = (l + r) / 2;
		buildTree(2 * node, l, mid, 0);
		buildTree(2 * node + 1, mid + 1, r, 0);
		if (l < m - 1) {
			tree[node] = mul(tree[2 * node], tree[2 * node + 1]);
		} else {
			tree[node] = tree[2 * node];
		}
	};

	if (m > 1) {
		buildTree(1, 0, m - 1, 0);
	} else {
		Mat d(sz);
		for (int i = 0; i < sz; ++i) {
			for (int j = 0; j < sz; ++j) d.a[i][j] = INF;
			d.a[i][i] = 0;
		}
		for (int i = 0; i < sz; ++i) {
			priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
			vector<ll> dist(sz, INF);
			dist[i] = 0;
			pq.push({0, i});
			while (!pq.empty()) {
				auto [d_val, u] = pq.top();
				pq.pop();
				if (d_val > dist[u]) continue;
				int ur = u / 2, um = u % 2;
				if (g[ur][0] == '.' && dist[u ^ 1] > dist[u] + 1) {
					dist[u ^ 1] = dist[u] + 1;
					pq.push({dist[u ^ 1], u ^ 1});
				}
				int dr[] = {1, -1};
				for (int d_idx = 0; d_idx < 2; ++d_idx) {
					int nr = ur + dr[d_idx];
					if (nr >= 0 && nr < n && ok(nr, 0, um)) {
						int v = nr * 2 + um;
						if (dist[v] > dist[u] + 1) {
							dist[v] = dist[u] + 1;
							pq.push({dist[v], v});
						}
					}
				}
			}
			for (int j = 0; j < sz; ++j) d.a[i][j] = dist[j];
		}
		tree[1] = d;
	}

	function<Mat(int, int, int, int, int)> queryTree = [&](int node, int l, int r, int ql, int qr) -> Mat {
		if (ql <= l && r <= qr) return tree[node];
		int mid = (l + r) / 2;
		if (qr <= mid) return queryTree(2 * node, l, mid, ql, qr);
		if (ql > mid) return queryTree(2 * node + 1, mid + 1, r, ql, qr);
		return mul(queryTree(2 * node, l, mid, ql, qr), queryTree(2 * node + 1, mid + 1, r, ql, qr));
	};

	while (q--) {
		int r1, c1, r2, c2;
		ll lim;
		cin >> r1 >> c1 >> r2 >> c2 >> lim;

		int s = r1 * 2 + 0;
		ll ans = INF;

		if (c1 == c2) {
			Mat mat = queryTree(1, 0, m - 1, c1, c1);
			for (int m_idx = 0; m_idx < 2; ++m_idx) {
				int e = r2 * 2 + m_idx;
				ans = min(ans, mat.a[s][e]);
			}
		} else if (c1 < c2) {
			Mat mat = queryTree(1, 0, m - 1, c1, c2 - 1);
			for (int m_idx = 0; m_idx < 2; ++m_idx) {
				int e = r2 * 2 + m_idx;
				ans = min(ans, mat.a[s][e]);
			}
		} else {
			ans = INF;
		}

		if (ans <= lim) {
			cout << "YES\n";
		} else {
			cout << "NO\n";
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	if (cin >> t) {
		while (t--) {
			solve();
		}
	}
	return 0;
}