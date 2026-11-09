#include <bits/stdc++.h>
#include <cassert>

int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(nullptr);
	int T; std::cin >> T;
	while (T--) {
		int N; long long K; std::cin >> N >> K;
		struct Drone {
			int s, x;
			char d;
		};
		std::vector<Drone> A(N);
		for (auto& [s, x, d] : A) {
			int X, Y, Z;
			std::cin >> X >> Y >> Z >> d;
			s = X + Y;
			x = X;
		}
		std::sort(A.begin(), A.end(), [](const Drone& a, const Drone& b) {
			if (a.s != b.s) return a.s < b.s;
			return a.x < b.x;
		});
		std::vector<int> pref(N + 1);
		for (int i = 0; i < N; i++) {
			pref[i + 1] = pref[i] + (A[i].d == 'N');
		}
		long long bad = 0;
		for (int l = 0; l < N;) {	
			int r = l;
			while (r < N && A[r].s == A[l].s) r++; // proc grp
			int p = l;
			for (int i = l; i < r; i++) {
				if (A[i].d == 'E') {
					p = std::max(p, i + 1);
					while (p < r && A[p].x - A[i].x < K) p++;
					bad += pref[p] - pref[i + 1];
				}
			} l = r;
		} std::cout << 1LL * N * K - bad << '\n';
	}

	return 0;
}
