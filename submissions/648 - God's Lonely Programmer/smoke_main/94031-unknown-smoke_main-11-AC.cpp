#include <bits/stdc++.h>
#include <cassert>

int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(nullptr);
	int T; std::cin >> T;
	while (T--) {
		int N; long long R; std::cin >> N >> R;
		std::queue<long long> ready;
		bool ok = true;
		for (int i = 0; i < N; i++) {
			long long t; std::cin >> t;
			if (!ok) continue;
			while (!ready.empty() && ready.front() <= t) ready.pop();
			if (ready.size() == 2) {
				ok = false;
				continue;
			}
			long long start = ready.empty() ? t : ready.back();
			ready.push(start + R);
		}
		std::cout << (ok ? "YES\n" : "NO\n");
	}

	return 0;
}
