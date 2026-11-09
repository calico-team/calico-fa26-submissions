#include <bits/stdc++.h>
#include <cassert>

int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(nullptr);
	int T; std::cin >> T;
	while (T--) {
		int N, K; std::cin >> N >> K;
		std::vector<char> A(K); for (auto& c : A) std::cin >> c;
		std::string S(N, '?');
		for (char c : A) {
			std::string G = S;
			for (auto& x : G) if (x == '?') x = c;
			std::cout << G << '\n' << std::flush;
			std::string res; std::cin >> res;
			if (res == "CORRECT") break;
			assert(int(res.size()) == N);
			for (int i = 0; i < N; i++) {
				if (res[i] != '_') S[i] = res[i];
			}
		}
	}

	return 0;
}
