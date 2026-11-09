#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
using namespace std;

struct Trie {
	vector<array<int, 2>> ch;
	vector<int> cnt;

	void reset() {
		ch.assign(1, array<int, 2>{0, 0});
		cnt.assign(1, 0);
	}

	void add(int x, int d) {
		int n = 0;
		for (int bit = 29; bit >= 0; bit--) {
			int b = x >> bit & 1;
			if (!ch[n][b]) {
				ch[n][b] = ch.size();
				ch.push_back({0, 0});
				cnt.push_back(0);
			}
			n = ch[n][b];
			cnt[n] += d;
		}
	}

	int best(int q) {
		int n = 0, top = 0;
		for (int bit = 29; bit >= 0; bit--) {
			int b = q >> bit & 1;
			int want = ch[n][b ^ 1], same = ch[n][b];
			if (want && cnt[want]) {
				n = want;
				top |= 1 << bit;
			} else if (same && cnt[same]) {
				n = same;
			} else {
				break;
			}
		}
		return top;
	}
};


vector<int> solve(int N, vector<int> A, vector<int> V) {
	vector<int> to(N), state(N), Q(N), X(N), entryQ(N), h(N);
	vector<char> inCycle(N);
	vector<vector<int>> kids(N), cycles;
	for (int i = 0; i < N; i++) to[i] = A[i] - 1;

	vector<int> path;
	for (int s = 0; s < N; s++) {
		if (state[s]) continue;
		int v = s;
		while (!state[v]) {
			state[v] = 1;
			path.push_back(v);
			v = to[v];
		}
		if (state[v] == 1) {
			auto at = find(path.begin(), path.end(), v);
			cycles.emplace_back(at, path.end());
			for (auto it = at; it != path.end(); ++it) inCycle[*it] = 1;
		}
		for (int u : path) state[u] = 2;
		path.clear();
	}
	for (int i = 0; i < N; i++)
		if (!inCycle[i]) kids[to[i]].push_back(i);

	Trie ring, tree;
	vector<int> stack;
	for (auto& cycle : cycles) {
		int C = 0;
		ring.reset();
		for (int c : cycle) {
			Q[c] = C;
			C ^= V[c];
			ring.add(Q[c], 1);
		}
		for (int c : cycle) {
			entryQ[c] = Q[c];
			h[c] = max(ring.best(Q[c]), ring.best(Q[c] ^ C));
			for (int k : kids[c]) stack.push_back(k);
		}
		tree.reset();
		while (!stack.empty()) {
			int v = stack.back();
			stack.pop_back();
			if (v < 0) {
				tree.add(Q[~v], -1);
				continue;
			}
			X[v] = V[v] ^ X[to[v]];
			entryQ[v] = entryQ[to[v]];
			Q[v] = X[v] ^ entryQ[v];
			h[v] = max({ring.best(Q[v]), ring.best(Q[v] ^ C), tree.best(Q[v])});
			tree.add(Q[v], 1);
			stack.push_back(~v);
			for (int k : kids[v]) stack.push_back(k);
		}
	}
	return h;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T; cin >> T;
	while (T--) {
		int N; cin >> N;
        vector<int> A(N), V(N);
        for (int& i : A) cin >> i;
        for (int& i : V) cin >> i;
        vector<int> ans = solve(N, A, V);
        for (int& i : ans) cout << i << ' ';
        cout << '\n';
	}
	return 0;
}
