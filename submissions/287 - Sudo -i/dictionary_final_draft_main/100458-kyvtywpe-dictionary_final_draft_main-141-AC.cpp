#include <iostream>
#include <vector>
using namespace std;

class XorTrie {
	struct Node {
		int child[2] = {-1, -1};
		int count = 0;
	};

	vector<Node> trie;

public:
	XorTrie() {
		clear();
	}

	void clear() {
		trie.clear();
		trie.emplace_back();
	}

	void insert(int value) {
		int node = 0;
		++trie[node].count;
		for (int bit = 29; bit >= 0; --bit) {
			int direction = (value >> bit) & 1;
			if (trie[node].child[direction] == -1) {
				int next_node = trie.size();
				trie[node].child[direction] = next_node;
				trie.emplace_back();
			}
			node = trie[node].child[direction];
			++trie[node].count;
		}
	}

	void erase(int value) {
		int node = 0;
		--trie[node].count;
		for (int bit = 29; bit >= 0; --bit) {
			node = trie[node].child[(value >> bit) & 1];
			--trie[node].count;
		}
	}

	// try the opposite bit first to make the xor larger
	int best_xor(int value) const {
		int node = 0;
		int result = 0;
		for (int bit = 29; bit >= 0; --bit) {
			int direction = (value >> bit) & 1;
			int opposite = trie[node].child[direction ^ 1];
			if (opposite != -1 && trie[opposite].count > 0) {
				result |= 1 << bit;
				node = opposite;
			} else {
				node = trie[node].child[direction];
			}
		}
		return result;
	}
};

/**
 * Return an array of N integers, the i-th of which
 * represents Big Ben's maximum happiness if he
 * starts by trying to define word i.
 *
 * N: the number of words in the dictionary
 * A: the first word in the definition of word i
 * V: the value associated with the happiness of each word
 */
vector<int> solve(int N, vector<int> A, vector<int> V) {
	for (int& i : A) --i;

	vector<int> incoming(N, 0);
	vector<int> child_head(N, -1);
	vector<int> sibling(N, -1);
	for (int u = 0; u < N; ++u) {
		int v = A[u];
		++incoming[v];
		sibling[u] = child_head[v];
		child_head[v] = u;
	}

	// peel off the trees; only cycles stay
	vector<int> pending;
	pending.reserve(N);
	for (int u = 0; u < N; ++u) {
		if (incoming[u] == 0) pending.push_back(u);
	}
	for (size_t head = 0; head < pending.size(); ++head) {
		int v = A[pending[head]];
		if (--incoming[v] == 0) pending.push_back(v);
	}

	vector<unsigned char> in_cycle(N);
	for (int u = 0; u < N; ++u) in_cycle[u] = incoming[u] > 0;

	vector<int> path_xor(N, 0);
	vector<int> best(N, -1);
	vector<int> loop;
	vector<int> dfs_stack;
	loop.reserve(N);
	dfs_stack.reserve(N);
	XorTrie trie;

	for (int start = 0; start < N; ++start) {
		if (!in_cycle[start] || best[start] != -1) continue;

		loop.clear();
		int loop_xor = 0;
		int u = start;
		do {
			loop.push_back(u);
			path_xor[u] = loop_xor;
			loop_xor ^= V[u];
			u = A[u];
		} while (u != start);

		// one lap changes the xor by loop_xor; after two laps it repeats
		// so these two sets cover every possible stopping point
		trie.clear();
		for (int vertex : loop) {
			trie.insert(path_xor[vertex]);
			if (loop_xor != 0) {
				trie.insert(path_xor[vertex] ^ loop_xor);
			}
		}
		for (int vertex : loop) {
			best[vertex] = trie.best_xor(path_xor[vertex]);
		}

		// use a stack to avoid recursion on long chains
		// positive means enter, negative means leave
		for (int root : loop) {
			for (int child = child_head[root]; child != -1;
				child = sibling[child]) {
				if (!in_cycle[child]) dfs_stack.push_back(child + 1);
			}
			while (!dfs_stack.empty()) {
				int entry = dfs_stack.back();
				dfs_stack.pop_back();
				if (entry < 0) {
					trie.erase(path_xor[-entry - 1]);
					continue;
				}

				int vertex = entry - 1;
				path_xor[vertex] = V[vertex] ^ path_xor[A[vertex]];
				// keep the reachable stops for this branch in the trie
				best[vertex] = trie.best_xor(path_xor[vertex]);
				trie.insert(path_xor[vertex]);
				dfs_stack.push_back(-entry);
				for (int child = child_head[vertex]; child != -1;
					child = sibling[child]) {
					dfs_stack.push_back(child + 1);
				}
			}
		}
	}
	return best;
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
