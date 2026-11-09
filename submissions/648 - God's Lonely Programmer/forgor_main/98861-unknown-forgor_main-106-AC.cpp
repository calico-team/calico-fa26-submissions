#include <bits/stdc++.h>
#include <cassert>

struct input_t {
	std::string phase;
	int N;
	std::vector<std::array<int, 2>> edges;
	std::vector<int> A;
};

input_t read_your_input();
int main() {
	std::ios_base::sync_with_stdio(false), std::cin.tie(nullptr);
	auto in = read_your_input();
	int N = in.N;
	if (in.phase == "FIRST") {
		std::vector<std::vector<int>> adj(N);
		std::vector<int> deg(N, 0);
		for (auto [u, v] : in.edges) {
			u--, v--;
			adj[u].push_back(v);
			adj[v].push_back(u);
			deg[u]++, deg[v]++;
		}
		std::priority_queue<int, std::vector<int>, std::greater<int>> leaves;
		for (int i = 0; i < N; i++) {
			if (deg[i] == 1) leaves.push(i);
		}
		std::vector<int> code; code.reserve(N-2);
		for (int i = 0; i < N-2; i++) {
			assert(!leaves.empty());
			int v = leaves.top(); leaves.pop();
			int u = -1;
			for (int w : adj[v]) {
				if (deg[w] > 0) {
					u = w;
					break;
				}
			}
			assert(u != -1);
			code.push_back(u+1);
			deg[v] = 0;
			deg[u]--;
			if (deg[u] == 1) leaves.push(u);
		}
		std::vector<int> A(N, 0);
		int mod = N+1, sum = 0;
		for (int i = 0; i < N-2; i++) {
			A[i] = code[i];
			sum = (sum + code[i]) % mod;
		}
		A[N-2] = sum;
		for (int i = 0; i < N; i++) {
			std::cout << A[i] << " \n"[i+1==N];
		}
	} else {
		assert(in.phase == "SECOND");
		int missing = -1;
		for (int i = 0; i < N; i++) {
			if (in.A[i] == -1) missing = i;
		}
		assert(missing != -1);
		std::vector<int> code(N-2);
		for (int i = 0; i < N-2; i++) code[i] = in.A[i];
		if (missing < N-2) {
			int mod = N+1, sum = 0;
			for (int i = 0; i < N-2; i++) {
				if (i != missing) sum = (sum + code[i]) % mod;
			}
			code[missing] = (in.A[N-2] - sum + mod) % mod;
			assert(1 <= code[missing] && code[missing] <= N);
		}
		std::vector<int> deg(N, 1);
		for (int x : code) deg[x-1]++;
		std::priority_queue<int, std::vector<int>, std::greater<int>> leaves;
		for (int i = 0; i < N; i++) {
			if (deg[i] == 1) leaves.push(i);
		}
		for (int x : code) {
			assert(!leaves.empty());
			int v = leaves.top(); leaves.pop();
			int u = x-1;
			std::cout << v+1 << ' ' << u+1 << '\n';
			deg[v]--;
			deg[u]--;
			if (deg[u] == 1) leaves.push(u);
		}
		int u = -1, v = -1;
		for (int i = 0; i < N; i++) {
			if (deg[i] == 1) {
				if (u == -1) u = i;
				else v = i;
			}
		}
		assert(u != -1 && v != -1);
		std::cout << u+1 << ' ' << v+1 << '\n';
	}
	return 0;
}
input_t read_your_input() {
	input_t in;
	std::cin >> in.phase >> in.N;
	if (in.phase == "FIRST") {
		in.edges.resize(in.N-1);
		for (auto& [u, v] : in.edges) std::cin >> u >> v;
	} else {
		assert(in.phase == "SECOND");
		in.A.resize(in.N);
		for (auto& a : in.A) std::cin >> a;
	}
	return in;
}
