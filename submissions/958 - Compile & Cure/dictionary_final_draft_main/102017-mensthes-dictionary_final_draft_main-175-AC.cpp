#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int BITS = 30;
const int MAX_NODES = 30 * 200000 + 100;
int child[MAX_NODES][2];
int cnt[MAX_NODES];
int used;

int newNode() {
    child[used][0] = child[used][1] = 0;
    cnt[used] = 0;
    return used++;
}

void trieAdd(int root, int v, int delta) {
    int node = root;
    for (int b = BITS - 1; b >= 0; b--) {
        int bit = (v >> b) & 1;
        if (!child[node][bit]) {
            int fresh = newNode();
            child[node][bit] = fresh;
        }
        node = child[node][bit];
        cnt[node] += delta;
    }
}

int trieMax(int root, int q) {
    int node = root, res = 0;
    for (int b = BITS - 1; b >= 0; b--) {
        int bit = (q >> b) & 1;
        int want = child[node][bit ^ 1];
        if (want && cnt[want] > 0) {
            res |= 1 << b;
            node = want;
        } else {
            node = child[node][bit];
        }
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
    // YOUR CODE HERE
    vector<int> nxt(N);
    for (int i = 0; i < N; i++) nxt[i] = A[i] - 1;

    vector<int> color(N, 0);
    vector<char> onCycle(N, 0);
    vector<vector<int>> cycles;
    for (int s = 0; s < N; s++) {
        if (color[s]) continue;
        vector<int> path;
        int x = s;
        while (color[x] == 0) {
            color[x] = 1;
            path.push_back(x);
            x = nxt[x];
        }
        if (color[x] == 1) {
            vector<int> cyc;
            int y = x;
            do {
                cyc.push_back(y);
                onCycle[y] = 1;
                y = nxt[y];
            } while (y != x);
            cycles.push_back(cyc);
        }
        for (int y : path) color[y] = 2;
    }

    vector<vector<int>> children(N);
    for (int i = 0; i < N; i++)
        if (!onCycle[i]) children[nxt[i]].push_back(i);

    vector<int> ans(N, 0), T(N, 0);
    for (auto& cyc : cycles) {
        int L = cyc.size();
        vector<int> Z(L + 1, 0);
        for (int t = 0; t < L; t++) Z[t + 1] = Z[t] ^ V[cyc[t]];
        int C = Z[L];

        used = 1;
        int cycRoot = newNode();
        int pathRoot = newNode();
        for (int r = 0; r < L; r++) trieAdd(cycRoot, Z[r], 1);

        for (int j = 0; j < L; j++) {
            int c = cyc[j];
            ans[c] = max(trieMax(cycRoot, Z[j]), trieMax(cycRoot, Z[j] ^ C));

            trieAdd(pathRoot, 0, 1);
            vector<int> st(children[c].begin(), children[c].end());
            while (!st.empty()) {
                int x = st.back();
                st.pop_back();
                if (x >= 0) {
                    T[x] = V[x] ^ T[nxt[x]];
                    int q = T[x] ^ Z[j];
                    ans[x] = max(trieMax(pathRoot, T[x]),
                                 max(trieMax(cycRoot, q), trieMax(cycRoot, q ^ C)));
                    trieAdd(pathRoot, T[x], 1);
                    st.push_back(~x);
                    for (int ch : children[x]) st.push_back(ch);
                } else {
                    trieAdd(pathRoot, T[~x], -1);
                }
            }
            trieAdd(pathRoot, 0, -1);
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