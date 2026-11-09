#include <bits/stdc++.h>
#include <cassert>

static constexpr int INF = 1'000'000'000;

void floyd(int* D, int W) {
	for (int k = 0; k < W; k++) {
		const int* dk = D + k*W;
		for (int i = 0; i < W; i++) {
			int* di = D + i*W;
			int x = di[k];
			if (x >= INF) continue;
			for (int j = 0; j < W; j++) di[j] = std::min(di[j], x + dk[j]);
		}
	}
}

void matmul(const int* A, const int* B, int* C, int W) {
	std::fill(C, C + W*W, INF);
	for (int i = 0; i < W; i++) {
		int* ci = C + i*W;
		const int* ai = A + i*W;
		for (int k = 0; k < W; k++) {
			int x = ai[k];
			if (x >= INF) continue;
			const int* bk = B + k*W;
			for (int j = 0; j < W; j++) ci[j] = std::min(ci[j], x + bk[j]);
		}
	}
}

bool active(char c, int z) {
	return c == '.' || c == (z == 0 ? 'B' : 'R');
}

void local_metric(const std::vector<std::string>& G, int c, int W, int* D) {
	int N = W/2;
	std::fill(D, D + W*W, INF);
	int adj[20][6], deg[20]{};
	for (int r = 0; r < N; r++) {
		for (int z = 0; z < 2; z++) {
			if (!active(G[r][c], z)) continue;
			int v = 2*r+z;
			if (G[r][c] == '.') adj[v][deg[v]++] = 2*r+1-z;
			for (int nr : {r-1, r+1}) {
				if (0 <= nr && nr < N && active(G[nr][c], z)) adj[v][deg[v]++] = 2*nr+z;
			}
		}
	}
	int q[20];
	for (int s = 0; s < W; s++) {
		if (!active(G[s/2][c], s%2)) continue;
		int h = 0, t = 0;
		D[s*W+s] = 0;
		q[t++] = s;
		while (h < t) {
			int v = q[h++];
			for (int z = 0; z < deg[v]; z++) {
				int u = adj[v][z];
				if (D[s*W+u] != INF) continue;
				D[s*W+u] = D[s*W+v] + 1;
				q[t++] = u;
			}
		}
	}
}

void extend_metric(
	const int* DA, const int* DB,
	const std::vector<std::string>& G, int ca, int cb, int W,
	int* Dnext, int* Cross
) {
	int N = W/2;
	int ports_a[20], ports_b[20], P = 0;
	for (int r = 0; r < N; r++) {
		for (int z = 0; z < 2; z++) {
			if (active(G[r][ca], z) && active(G[r][cb], z)) {
				ports_a[P] = ports_b[P] = 2*r+z;
				P++;
			}
		}
	}
	if (Dnext) std::copy(DB, DB+W*W, Dnext);
	if (Cross) std::fill(Cross, Cross+W*W, INF);
	if (P == 0) return;

	int E[400];
	for (int i = 0; i < P; i++) {
		for (int j = 0; j < P; j++) {
			int a = DA[ports_a[i]*W+ports_a[j]];
			int b = DB[ports_b[i]*W+ports_b[j]];
			E[i*P+j] = std::min(a, b < INF ? b+2 : INF);
		}
	}
	for (int k = 0; k < P; k++) {
		for (int i = 0; i < P; i++) {
			int x = E[i*P+k];
			if (x >= INF) continue;
			for (int j = 0; j < P; j++) E[i*P+j] = std::min(E[i*P+j], x+E[k*P+j]);
		}
	}

	if (Cross) {
		int L1[400];
		std::fill(L1, L1+W*P, INF);
		for (int a = 0; a < W; a++) {
			for (int i = 0; i < P; i++) {
				int x = DA[a*W+ports_a[i]];
				if (x >= INF) continue;
				for (int j = 0; j < P; j++) L1[a*P+j] = std::min(L1[a*P+j], x+E[i*P+j]);
			}
		}
		for (int a = 0; a < W; a++) {
			for (int b = 0; b < W; b++) {
				int best = INF;
				for (int j = 0; j < P; j++) {
					int x = L1[a*P+j], y = DB[ports_b[j]*W+b];
					if (x < INF && y < INF) best = std::min(best, x+1+y);
				}
				Cross[a*W+b] = best;
			}
		}
	}
	if (Dnext) {
		int L2[400];
		std::fill(L2, L2+W*P, INF);
		for (int b = 0; b < W; b++) {
			for (int i = 0; i < P; i++) {
				int x = DB[b*W+ports_b[i]];
				if (x >= INF) continue;
				for (int j = 0; j < P; j++) L2[b*P+j] = std::min(L2[b*P+j], x+1+E[i*P+j]);
			}
		}
		for (int b = 0; b < W; b++) {
			for (int c = 0; c < W; c++) {
				int best = Dnext[b*W+c];
				for (int j = 0; j < P; j++) {
					int x = L2[b*P+j], y = DB[ports_b[j]*W+c];
					if (x < INF && y < INF) best = std::min(best, x+1+y);
				}
				Dnext[b*W+c] = best;
			}
		}
	}
}

void apply_row(const int* A, int* v, int W) {
	int out[20];
	std::fill(out, out+W, INF);
	for (int i = 0; i < W; i++) {
		int x = v[i];
		if (x >= INF) continue;
		const int* row = A+i*W;
		for (int j = 0; j < W; j++) out[j] = std::min(out[j], x+row[j]);
	}
	std::copy(out, out+W, v);
}

void apply_col(const int* A, int* v, int W) {
	int out[20];
	for (int i = 0; i < W; i++) {
		int best = INF;
		for (int j = 0; j < W; j++) best = std::min(best, A[i*W+j]+v[j]);
		out[i] = best;
	}
	std::copy(out, out+W, v);
}

int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(nullptr);
	int T; std::cin >> T;
	while (T--) {
		int N, M, Q; std::cin >> N >> M >> Q;
		int W = 2*N, W2 = W*W;
		std::vector<std::string> G(N);
		for (auto& row : G) std::cin >> row;
		std::vector<int> Dcol(M*W2), Left(M*W2), Right(M*W2), Glob(M*W2);
		for (int c = 0; c < M; c++) local_metric(G, c, W, Dcol.data()+c*W2);
		std::copy(Dcol.begin(), Dcol.begin()+W2, Left.begin());
		for (int c = 0; c+1 < M; c++) {
			extend_metric(Left.data()+c*W2, Dcol.data()+(c+1)*W2, G, c, c+1, W, Left.data()+(c+1)*W2, nullptr);
		}
		std::copy(Dcol.end()-W2, Dcol.end(), Right.end()-W2);
		for (int c = M-2; c >= 0; c--) {
			extend_metric(Right.data()+(c+1)*W2, Dcol.data()+c*W2, G, c+1, c, W, Right.data()+c*W2, nullptr);
		}
		for (int c = 0; c < M; c++) {
			int* D = Glob.data()+c*W2;
			for (int i = 0; i < W2; i++) D[i] = std::min(Left[c*W2+i], Right[c*W2+i]);
			floyd(D, W);
		}
		int L = M-1;
		std::vector<int> F(L*W2);
		for (int c = 0; c < L; c++) {
			extend_metric(Glob.data()+c*W2, Glob.data()+(c+1)*W2, G, c, c+1, W, nullptr, F.data()+c*W2);
		}
		int LOG = 0;
		while ((1 << LOG) < L) LOG++;
		std::vector<std::vector<int>> st(LOG, std::vector<int>(L*W2));
		for (int k = 0; k < LOG; k++) {
			int half = 1 << k, block = 2*half;
			for (int b = 0; b < L; b += block) {
				int mid = std::min(b+half, L), end = std::min(b+block, L);
				for (int i = mid-1; i >= b; i--) {
					int* dst = st[k].data()+i*W2;
					if (i == mid-1) std::copy(F.data()+i*W2, F.data()+(i+1)*W2, dst);
					else matmul(F.data()+i*W2, st[k].data()+(i+1)*W2, dst, W);
				}
				for (int i = b+half; i < end; i++) {
					int* dst = st[k].data()+i*W2;
					if (i == b+half) std::copy(F.data()+i*W2, F.data()+(i+1)*W2, dst);
					else matmul(st[k].data()+(i-1)*W2, F.data()+i*W2, dst, W);
				}
			}
		}

		while (Q--) {
			int rs, cs, re, ce;
			int64_t K;
			std::cin >> rs >> cs >> re >> ce >> K;
			assert(G[rs][cs] == '.');
			int s = 2*rs;
			int dst[2] = {2*re, 2*re+1};
			int ndst = G[re][ce] == '.' ? 2 : 1;
			if (ndst == 1 && G[re][ce] == 'R') dst[0]++;
			int best = INF;
			if (cs == ce) {
				const int* D = Glob.data()+ce*W2;
				for (int z = 0; z < ndst; z++) best = std::min(best, D[s*W+dst[z]]);
			} else if (cs < ce) {
				int v[20]; std::fill(v, v+W, INF); v[s] = 0;
				int len = ce-cs;
				if (len == 1) apply_row(F.data()+cs*W2, v, W);
				else {
					int k = 31-__builtin_clz(unsigned(cs^(ce-1)));
					apply_row(st[k].data()+cs*W2, v, W);
					apply_row(st[k].data()+(ce-1)*W2, v, W);
				}
				const int* D = Glob.data()+ce*W2;
				for (int a = 0; a < W; a++) for (int z = 0; z < ndst; z++) best = std::min(best, v[a]+D[a*W+dst[z]]);
			} else {
				int v[20]; std::fill(v, v+W, INF); v[s] = 0;
				int len = cs-ce;
				if (len == 1) apply_col(F.data()+ce*W2, v, W);
				else {
					int k = 31-__builtin_clz(unsigned(ce^(cs-1)));
					apply_col(st[k].data()+(cs-1)*W2, v, W);
					apply_col(st[k].data()+ce*W2, v, W);
				}
				const int* D = Glob.data()+ce*W2;
				for (int a = 0; a < W; a++) for (int z = 0; z < ndst; z++) best = std::min(best, v[a]+D[dst[z]*W+a]);
			}
			std::cout << (best < INF && best <= K ? "YES\n" : "NO\n");
		}
	}

	return 0;
}
