#include <iostream>
#include <vector>
using namespace std;

static int zeroC[6400005], oneC[6400005], cntC[6400005];
int nodes;

int fresh() { zeroC[nodes] = oneC[nodes] = cntC[nodes] = 0; return nodes++; }

void add(int t, int x, int d) {
    for (int b = 29; b >= 0; b--) {
        int* c = ((x >> b) & 1) ? oneC : zeroC;
        if (!c[t]) c[t] = fresh();
        t = c[t];
        cntC[t] += d;
    }
}

int best(int t, int x) {
    int res = 0;
    for (int b = 29; b >= 0; b--) {
        int y = ((x >> b) & 1) ? zeroC[t] : oneC[t];
        if (y && cntC[y]) { res |= 1 << b; t = y; }
        else t = ((x >> b) & 1) ? oneC[t] : zeroC[t];
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
    vector<int> nxt(N);
    for (int i = 0; i < N; i++) nxt[i] = A[i] - 1;
    vector<int> seen(N, 0), trail;
    vector<char> onCycle(N, 0);
    vector<vector<int>> loops;
    for (int s = 0; s < N; s++) {
        if (seen[s]) continue;
        trail.clear();
        int u = s;
        while (!seen[u]) { seen[u] = 1; trail.push_back(u); u = nxt[u]; }
        if (seen[u] == 1) {
            vector<int> ring = {u};
            onCycle[u] = 1;
            for (int w = nxt[u]; w != u; w = nxt[w]) { ring.push_back(w); onCycle[w] = 1; }
            loops.push_back(ring);
        }
        for (int p : trail) seen[p] = 2;
    }
    vector<vector<int>> kids(N);
    for (int u = 0; u < N; u++) if (!onCycle[u]) kids[nxt[u]].push_back(u);
    vector<int> out(N), depthXor(N, 0);
    for (auto& ring : loops) {
        nodes = 1;
        int L = ring.size();
        vector<int> pref(L);
        int acc = 0;
        for (int j = 0; j < L; j++) { acc ^= V[ring[j]]; pref[j] = acc; }
        int total = acc;
        int ringTrie = fresh();
        for (int x : pref) add(ringTrie, x, 1);
        int pathTrie = fresh();
        add(pathTrie, 0, 1);
        vector<int> st;
        for (int k = 0; k < L; k++) {
            int r = ring[k];
            int shift = k ? pref[k - 1] : 0;
            int a1 = best(ringTrie, shift), a2 = best(ringTrie, shift ^ total);
            out[r] = a1 > a2 ? a1 : a2;
            st.assign(kids[r].begin(), kids[r].end());
            while (!st.empty()) {
                int u = st.back(); st.pop_back();
                if (u < 0) { add(pathTrie, depthXor[~u], -1); continue; }
                int qu = V[u] ^ depthXor[nxt[u]];
                depthXor[u] = qu;
                int key = qu ^ shift;
                int b1 = best(pathTrie, qu), b2 = best(ringTrie, key), b3 = best(ringTrie, key ^ total);
                if (b2 > b1) b1 = b2;
                out[u] = b1 > b3 ? b1 : b3;
                add(pathTrie, qu, 1);
                st.push_back(~u);
                for (int w : kids[u]) st.push_back(w);
            }
        }
    }
    return out;
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