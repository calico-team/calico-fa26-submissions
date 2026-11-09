#include <bits/stdc++.h>
using namespace std;

int fold(int* c, int h) {
	int m = 0;
	for (int j = h - 1; j >= 0; j--) {
		if (c[j] > 1) return m | (2 << j) - 1;
		if (c[j]) m |= 1 << j;
	}
	return m;
}

int solve(int N, vector<int> L, vector<int> R) {
	int base = 0, hv[30] = {}, cnt[30] = {}, ans = 0, par = 0;
	vector<pair<int, int>> g[30];
	for (int i = 0; i < N; i++) {
		if (L[i] == R[i]) { base ^= L[i]; continue; }
		int b = 31 - __builtin_clz(L[i] ^ R[i]), m = (1 << b) - 1;
		int x = m ^ (L[i] & m), y = R[i] & m;
		base ^= (L[i] >> b << b) | m;
		g[b].push_back({max(x, y), min(x, y)});
		hv[b] ^= x < y;
	}
	for (int h = 29; h >= 0; h--) {
		int bit = (base >> h & 1) ^ par, full = (2 << h) - 1;
		if (g[h].empty()) {
			if (cnt[h] > 1 || cnt[h] && bit) { ans |= full; break; }
			if (cnt[h] || bit) ans |= 1 << h;
			continue;
		}
		if (cnt[h]) { ans |= full; break; }
		ans |= 1 << h;
		par ^= bit ^ 1;
		int gc[30] = {}, flip = -1, best = -1;
		for (auto [a, b] : g[h])
			for (int j = 0; j < h; j++) gc[j] += a >> j & 1;
		if (hv[h] != (bit ^ 1))
			for (int t = 0; t < (int)g[h].size(); t++) {
				int c[30], m;
				for (int j = 0; j < h; j++)
					c[j] = gc[j] - (g[h][t].first >> j & 1) + (g[h][t].second >> j & 1);
				if ((m = fold(c, h)) > best) best = m, flip = t;
			}
		for (int t = 0; t < (int)g[h].size(); t++) {
			int p = t == flip ? g[h][t].second : g[h][t].first;
			for (int j = 0; j < h; j++) cnt[j] += p >> j & 1;
		}
	}
	return ans;
}

int main() {
	int T; scanf("%d", &T);
	while (T--) {
		int N; scanf("%d", &N);
		vector<int> L(N), R(N);
		for (int& i : L) scanf("%d", &i);
		for (int& i : R) scanf("%d", &i);
		printf("%d\n", solve(N, L, R));
	}
}
