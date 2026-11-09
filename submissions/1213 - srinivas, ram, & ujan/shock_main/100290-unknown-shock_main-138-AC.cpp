#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> par;

int find(int x) {
	int y = x;
	while (par[y] != y) y = par[y];
	while (par[x] != y) {
		int nx = par[x];
		par[x] = y;
		x = nx;
	}
	return y;
}

void solve() {
	int N, M, Q;
	cin >> N >> M >> Q;
	vector<array<int, 3>> e(Q);
	for (auto &x : e) cin >> x[0] >> x[1] >> x[2];
	int W = M + 1; 
	par.assign(N * W, 0);
	iota(par.begin(), par.end(), 0);
	vector<int> ans(N * M, 0);
	for (int i = Q - 1; i >= 0; i--) {
		int R = e[i][0], C = e[i][1], P = e[i][2];
		for (int dy = 0; dy <= P; dy++) {
			int rem = P * P - dy * dy;
			int hw = sqrt(rem);
			while (hw * hw > rem) hw--;
			while ((hw + 1) * (hw + 1) <= rem) hw++;
			int lo = C - hw, hi = C + hw;
			for (int k = 0; k < 2; k++) {
				if (k == 1 && dy == 0) break;
				int r = (k == 0) ? R - dy : R + dy;
				int b = r * W;
				int x = find(b + lo);
				while (x - b <= hi) {
					int col = x - b;
					int dx = col - C;
					ans[r * M + col] = rem - dx * dx + 1;
					par[x] = x + 1;
					x = find(x + 1);
				}
			}
		}
	}
	for (int r = 0; r < N; r++) {
		for (int c = 0; c < M; c++) {
			cout << ans[r * M + c] << ' ';
		}
		cout << "\n";
	}
}

int32_t main() {
	int T;
	cin >> T;
	while (T--) solve();
}