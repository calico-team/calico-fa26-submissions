#include <iostream>
#include <vector>
using namespace std;

/**
 * Return an array of N integers, the i-th of which
 * represents Big Ben's maximum happiness if he
 * starts by trying to define word i.
 *
 * N: the number of words in the dictionary
 * A: the first word in the definition of word i
 * V: the value associated with the happiness of each word
 */

// binary trie over 30 bits, with counts so we can also remove numbers
static vector<int> ch0, ch1, cntv, freeNodes;

static int newNode() {
	if (!freeNodes.empty()) {
		int x = freeNodes.back();
		freeNodes.pop_back();
		return x;
	}
	ch0.push_back(0);
	ch1.push_back(0);
	cntv.push_back(0);
	return (int)ch0.size() - 1;
}

static void ins(int x) {
	int node = 0;
	for (int b = 29; b >= 0; b--) {
		int bit = (x >> b) & 1;
		int& slot = bit ? ch1[node] : ch0[node];
		if (!slot) {
			int nn = newNode();
			(bit ? ch1[node] : ch0[node]) = nn;
		}
		node = bit ? ch1[node] : ch0[node];
		cntv[node]++;
	}
}

static void del(int x) {
	int node = 0;
	for (int b = 29; b >= 0; b--) {
		int bit = (x >> b) & 1;
		int nx = bit ? ch1[node] : ch0[node];
		if (--cntv[nx] == 0) {
			(bit ? ch1[node] : ch0[node]) = 0;
			freeNodes.push_back(nx);
		}
		node = nx;
	}
}

static int best(int t) {
	int node = 0, res = 0;
	for (int b = 29; b >= 0; b--) {
		int bit = (t >> b) & 1;
		int want = bit ? ch0[node] : ch1[node];
		if (want) {
			res |= 1 << b;
			node = want;
		} else {
			node = bit ? ch1[node] : ch0[node];
		}
	}
	return res;
}

vector<int> solve(int N, vector<int> A, vector<int> V) {
	vector<int> nxt(N);
	for (int i = 0; i < N; i++) nxt[i] = A[i] - 1;

	// find cycles
	vector<int> state(N, 0);
	vector<char> onCycle(N, 0);
	vector<vector<int>> cycles;
	for (int s = 0; s < N; s++) {
		if (state[s]) continue;
		vector<int> path;
		int x = s;
		while (state[x] == 0) {
			state[x] = 1;
			path.push_back(x);
			x = nxt[x];
		}
		if (state[x] == 1) {
			vector<int> cyc;
			int k = (int)path.size() - 1;
			while (path[k] != x) k--;
			for (int j = k; j < (int)path.size(); j++) {
				cyc.push_back(path[j]);
				onCycle[path[j]] = 1;
			}
			cycles.push_back(cyc);
		}
		for (int u : path) state[u] = 2;
	}

	vector<vector<int>> kids(N);
	for (int i = 0; i < N; i++)
		if (!onCycle[i]) kids[nxt[i]].push_back(i);

	ch0.assign(1, 0);
	ch1.assign(1, 0);
	cntv.assign(1, 0);
	freeNodes.clear();

	vector<int> ans(N, 0), tag(N, 0);

	for (auto& cyc : cycles) {
		int L = cyc.size();
		vector<int> Q(L + 1, 0);
		for (int m = 0; m < L; m++) Q[m + 1] = Q[m] ^ V[cyc[m]];
		int C = Q[L];

		vector<int> base;
		for (int m = 0; m < L; m++) {
			base.push_back(Q[m]);
			if (C) base.push_back(Q[m] ^ C);
		}
		for (int x : base) ins(x);

		for (int a = 0; a < L; a++) {
			int u = cyc[a];
			tag[u] = Q[a];
			ans[u] = best(Q[a]);
			vector<int> st(kids[u].begin(), kids[u].end());
			while (!st.empty()) {
				int x = st.back();
				st.pop_back();
				if (x >= 0) {
					ins(tag[nxt[x]]);
					tag[x] = tag[nxt[x]] ^ V[x];
					ans[x] = best(tag[x]);
					st.push_back(~x);
					for (int c : kids[x]) st.push_back(c);
				} else {
					x = ~x;
					del(tag[nxt[x]]);
				}
			}
		}

		for (int x : base) del(x);
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
