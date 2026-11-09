#include <iostream>
#include <vector>
using namespace std;

static const int BITS = 30;

// Persistent binary trie over 30-bit values (shared arrays, reset per test).
static vector<int> ch0, ch1;

static int insertTrie(int prev, int x) {
	ch0.push_back(0); ch1.push_back(0);
	int newroot = (int)ch0.size() - 1;
	int cur = newroot;
	for (int b = BITS - 1; b >= 0; --b) {
		int c0 = ch0[prev], c1 = ch1[prev];
		ch0.push_back(0); ch1.push_back(0);
		int child = (int)ch0.size() - 1;
		if ((x >> b) & 1) { ch0[cur] = c0; ch1[cur] = child; prev = c1; }
		else              { ch0[cur] = child; ch1[cur] = c1; prev = c0; }
		cur = child;
	}
	return newroot;
}

static int maxXor(int root, int x) {
	int node = root, res = 0;
	for (int b = BITS - 1; b >= 0; --b) {
		if ((x >> b) & 1) {
			int c = ch0[node];
			if (c) { res |= (1 << b); node = c; } else node = ch1[node];
		} else {
			int c = ch1[node];
			if (c) { res |= (1 << b); node = c; } else node = ch0[node];
		}
	}
	return res;
}

vector<int> solve(int N, vector<int> A, vector<int> V) {
	vector<int> f(N);
	for (int i = 0; i < N; ++i) f[i] = A[i] - 1;

	ch0.assign(1, 0);
	ch1.assign(1, 0);

	vector<char> oncycle(N, 0);
	vector<int> node_root(N, 0), node_mask(N, 0), base_root(N, 0), cyc_C(N, 0);

	// find cycles in the functional graph
	vector<int> state(N, 0), pos(N, -1);
	vector<vector<int>> cycles;
	for (int s = 0; s < N; ++s) {
		if (state[s]) continue;
		vector<int> path;
		int u = s;
		while (state[u] == 0 && pos[u] == -1) {
			pos[u] = (int)path.size();
			path.push_back(u);
			u = f[u];
		}
		if (pos[u] != -1) {
			cycles.emplace_back(path.begin() + pos[u], path.end());
		}
		for (int v : path) { pos[v] = -1; state[v] = 2; }
	}

	// process each cycle: base trie over {pre[j]}, set roots/masks for cycle nodes
	for (auto& cyc : cycles) {
		int Lc = (int)cyc.size();
		vector<int> pre(Lc);
		int acc = 0;
		for (int j = 0; j < Lc; ++j) { acc ^= V[cyc[j]]; pre[j] = acc; }
		int C = pre[Lc - 1];
		int root = 0;
		for (int j = 0; j < Lc; ++j) root = insertTrie(root, pre[j]);
		for (int s = 0; s < Lc; ++s) {
			int c = cyc[s];
			oncycle[c] = 1;
			node_root[c] = root;
			node_mask[c] = (s > 0) ? pre[s - 1] : 0;
			base_root[c] = root;
			cyc_C[c] = C;
		}
	}

	// reverse adjacency (trees hanging off cycles)
	vector<int> head(N, -1), nxt(N), who(N);
	for (int i = 0; i < N; ++i) { int p = f[i]; who[i] = i; nxt[i] = head[p]; head[p] = i; }

	vector<int> ans(N, 0), stk;
	for (auto& cyc : cycles) {
		for (int c : cyc) {
			ans[c] = max(maxXor(base_root[c], node_mask[c]),
			             maxXor(base_root[c], node_mask[c] ^ cyc_C[c]));
			for (int i = head[c]; i != -1; i = nxt[i])
				if (!oncycle[i]) stk.push_back(i);
		}
	}

	while (!stk.empty()) {
		int i = stk.back(); stk.pop_back();
		int p = f[i];
		node_root[i] = insertTrie(node_root[p], node_mask[p]);
		node_mask[i] = V[i] ^ node_mask[p];
		base_root[i] = base_root[p];
		cyc_C[i] = cyc_C[p];
		ans[i] = max(maxXor(node_root[i], node_mask[i]),
		             maxXor(base_root[i], node_mask[i] ^ cyc_C[i]));
		for (int j = head[i]; j != -1; j = nxt[j]) stk.push_back(j);
	}

	return ans;
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
