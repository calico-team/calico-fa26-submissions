#include <bits/stdc++.h>
#include <cassert>

struct par_compressor { // blob/master/IOI2021/day1/keys/keys.cpp
	mutable std::vector<int> par;
	explicit par_compressor(int N) : par(N, -1) {}
	int get_par(int a) const {
		while (par[a] >= 0) {
			if (par[par[a]] >= 0) par[a] = par[par[a]];
			a = par[a];
		}
		return a;
	}
	void set_par(int a, int b) {
		assert(par[a] < 0 && par[b] < 0);
		assert(a != b);
		par[b] += par[a];
		par[a] = b;
	}
};

int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(nullptr);
	int T; std::cin >> T;
	while (T--) {
		int N, M, Q; std::cin >> N >> M >> Q;
		struct earthquake {
			int r, c, p;
		};
		std::vector<earthquake> E(Q);
		for (auto& [r, c, p] : E) std::cin >> r >> c >> p;
		std::vector<int> ans(N * M, 0);
		par_compressor uf(N * (M + 1));
		for (int i = Q-1; i >= 0; i--) {
			auto [R, C, P] = E[i];
			for (int dy = -P; dy <= P; dy++) {
				int sq = P*P - dy * dy;
				int dx = int(std::sqrt(double(sq)));
				while ((dx + 1)*(dx + 1) <= sq) dx++;
				while (dx*dx > sq) dx--;
				int r = R + dy;
				int base = r * (M + 1);
				int l = base+C-dx, h = base+C+dx;
				int x = uf.get_par(l);
				while (x <= h) {
					int c = x-base;
					ans[r*M+c] = sq - (c-C) * (c-C) + 1;
					int y = uf.get_par(x + 1);
					uf.set_par(x, y);
					x = y;
				}
			}
		} for (int r = 0; r < N; r++) {
			    for (int c = 0; c < M; c++) {
				    std::cout << ans[r*M+c] << " \n"[c + 1 == M];
			}
		}
	}

	return 0;
}
