#include <bits/stdc++.h>
#include <cassert>

int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(nullptr);
	int T; std::cin >> T;
	while (T--) {
		int N, M, Q; std::cin >> N >> M >> Q;
		std::vector<std::string> G(N);
		for (auto& row : G) std::cin >> row;
		auto id = [M](int r, int c, int z) -> int {
			return 2*(r*M+c)+z;
		};
		auto active = [](char c, int z) -> bool {
			return c == '.' || c == (z == 0 ? 'B' : 'R');
		};

		int dr[4] = {-1, 1, 0, 0};
		int dc[4] = {0, 0, -1, 1};
		std::vector<int> comp(2*N*M, -1);
		std::vector<int> q; q.reserve(2*N*M);
		int num_comps = 0;
		for (int s = 0; s < 2*N*M; s++) {
			int sr = s/(2*M), sc = s/2%M, sz = s%2;
			if (comp[s] != -1 || !active(G[sr][sc], sz)) continue;
			comp[s] = num_comps;
			q.clear(); q.push_back(s);
			for (int i = 0; i < int(q.size()); i++) {
				int v = q[i];
				int r = v/(2*M), c = v/2%M, z = v%2;
				if (G[r][c] == '.' && comp[v^1] == -1) {
					comp[v^1] = num_comps;
					q.push_back(v^1);
				}
				for (int d = 0; d < 4; d++) {
					int nr = r+dr[d], nc = c+dc[d];
					if (nr < 0 || nr >= N || nc < 0 || nc >= M) continue;
					if (!active(G[nr][nc], z)) continue;
					int u = id(nr, nc, z);
					if (comp[u] == -1) {
						comp[u] = num_comps;
						q.push_back(u);
					}
				}
			} num_comps++;
		}
		while (Q--) {
			int rs, cs, re, ce; std::cin >> rs >> cs >> re >> ce;
			assert(G[rs][cs] == '.');
			int s = id(rs, cs, 0);
			int e = id(re, ce, G[re][ce] == 'R');
			std::cout << (comp[s] == comp[e] ? "YES\n" : "NO\n");
		}
	}

	return 0;
}
