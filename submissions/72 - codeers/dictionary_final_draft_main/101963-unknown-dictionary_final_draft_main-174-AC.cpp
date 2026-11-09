#include <iostream>
#include <vector>
using namespace std;

static int pch[2][6200100], pcnt;   
static int cch[2][6000100], ccnt;  

static int pins(int prev, int x) {
	int r = ++pcnt, cur = r;
	for (int b = 29; b >= 0; b--) {
		int bit = (x >> b) & 1;
		pch[0][cur] = pch[0][prev];
		pch[1][cur] = pch[1][prev];
		int nn = ++pcnt;
		pch[bit][cur] = nn;
		prev = pch[bit][prev];
		cur = nn;
	}
	pch[0][cur] = pch[1][cur] = 0;
	return r;
}
static int pq(int root, int x) {
	if (!root) return 0;
	int cur = root, res = 0;
	for (int b = 29; b >= 0; b--) {
		int bit = (x >> b) & 1, w = bit ^ 1;
		if (pch[w][cur]) { res |= 1 << b; cur = pch[w][cur]; }
		else cur = pch[bit][cur];
	}
	return res;
}
static int newc() { ++ccnt; cch[0][ccnt] = cch[1][ccnt] = 0; return ccnt; }
static void cins(int x) {
	int cur = 1;
	for (int b = 29; b >= 0; b--) {
		int bit = (x >> b) & 1;
		if (!cch[bit][cur]) { int n = newc(); cch[bit][cur] = n; }
		cur = cch[bit][cur];
	}
}
static int cq(int x) {
	int cur = 1, res = 0;
	for (int b = 29; b >= 0; b--) {
		int bit = (x >> b) & 1, w = bit ^ 1;
		if (cch[w][cur]) { res |= 1 << b; cur = cch[w][cur]; }
		else cur = cch[bit][cur];
	}
	return res;
}

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
	for (int& a : A) a--; 

	vector<int> indeg(N, 0), order, q;
	for (int i = 0; i < N; i++) indeg[A[i]]++;
	for (int i = 0; i < N; i++) if (!indeg[i]) q.push_back(i);
	for (size_t h = 0; h < q.size(); h++) {
		int u = q[h];
		order.push_back(u);
		if (--indeg[A[u]] == 0) q.push_back(A[u]);
	}
	vector<char> onc(N, 0);
	for (int i = 0; i < N; i++) if (indeg[i] > 0) onc[i] = 1;

	vector<int> cid(N, -1), Sval(N, 0), Cx;
	vector<vector<int>> cycles;
	for (int i = 0; i < N; i++) if (onc[i] && cid[i] < 0) {
		int k = cycles.size();
		cycles.push_back({});
		int u = i, s = 0;
		while (cid[u] < 0) {
			cid[u] = k;
			Sval[u] = s;
			s ^= V[u];
			cycles[k].push_back(u);
			u = A[u];
		}
		Cx.push_back(s);
	}

	vector<int> X(N, 0), root(N, 0), ent(N, 0), ans(N, 0);
	for (int i = 0; i < N; i++) if (onc[i]) X[i] = V[i];
	pcnt = 0;
	vector<vector<int>> tails(cycles.size());
	for (int idx = (int)order.size() - 1; idx >= 0; idx--) {
		int i = order[idx];
		int p = A[i];
		X[i] = V[i] ^ X[p];
		int base = onc[p] ? 0 : root[p];
		root[i] = pins(base, X[p]);
		ent[i] = onc[p] ? p : ent[p];
		tails[cid[ent[i]]].push_back(i);
	}

	for (size_t k = 0; k < cycles.size(); k++) {
		ccnt = 0;
		newc();  
		int C = Cx[k];
		for (int u : cycles[k]) cins(Sval[u]);
		for (int u : cycles[k]) {
			ans[u] = max(cq(Sval[u]), cq(Sval[u] ^ C));
		}
		for (int i : tails[k]) {
			int e = ent[i];
			int x = X[i] ^ Sval[e] ^ V[e];
			ans[i] = max(pq(root[i], X[i]), max(cq(x), cq(x ^ C)));
		}
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