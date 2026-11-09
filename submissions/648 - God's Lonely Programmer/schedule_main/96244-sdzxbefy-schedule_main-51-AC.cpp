#include <bits/stdc++.h>
#include <cassert>

int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(nullptr);
	int T; std::cin >> T;
	while (T--) {
		int N, M, K; std::cin >> N >> M >> K;
		std::vector<std::vector<int>> ch(N+1);
		for (int i = 1; i <= N; i++) {
			int p; std::cin >> p;
			ch[p].push_back(i);
		}
		std::vector<int> order; order.reserve(N+1);
		order.push_back(0);
		for (int i = 0; i < int(order.size()); i++) {
			for (int v : ch[order[i]]) order.push_back(v);
		}
		std::vector<int> h(N+1, 1);
		for (int i = N; i > 0; i--) {
			int v = order[i];
			for (int u : ch[v]) h[v] = std::max(h[v], h[u]+1);
		}
		std::priority_queue<std::pair<int, int>> pq;
		for (int v : ch[0]) pq.push({h[v], v});
		int ans = 0;
		std::vector<int> taken; taken.reserve(K);
		for (int t = 0; t < M && !pq.empty(); t++) {
			taken.clear();
			for (int i = 0; i < K && !pq.empty(); i++) {
				int v = pq.top().second; pq.pop();
				ans++;
				taken.push_back(v);
			}
			for (int v : taken) {
				for (int u : ch[v]) pq.push({h[u], u});
			}
		} std::cout << ans << '\n';
	}

	return 0;
}
