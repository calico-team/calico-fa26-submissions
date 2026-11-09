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
vector<int> solve(int N, vector<int> A, vector<int> V) {
	// YOUR CODE HERE
    vector<int> ans(N, 0);
    vector<int> state(N, 0);
    vector<int> d;

    for (int &x : A) x--;

    auto dfs = [&](int u, auto&& dfs) -> void {
        if (state[u] == 2) return;
        if (state[u] == 1) return;

        state[u] = 1;
        d.push_back(u);

        int nxt = A[u];

        if (state[nxt] == 0) {
            dfs(nxt, dfs);
        }

        d.pop_back();

        ans[u] = V[u];

        if (state[nxt] == 2) {
            ans[u] = max(ans[u], V[u] ^ ans[nxt]);
        }

        state[u] = 2;
    };

    for (int i = 0; i < N; i++) {
        if (state[i] == 0) {
            dfs(i, dfs);
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