#include <bits/stdc++.h>
#define int long long
using namespace std;

int N, M, K;
vector<int> prereq, height;
vector<vector<int>> children;

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int T;
	cin >> T;

	while (T--) {
		cin >> N >> M >> K;

		prereq.assign(N + 1, 0);
		children.assign(N + 1, {});

		for (int i = 1; i <= N; i++) {
			cin >> prereq[i];
			if (prereq[i] != 0) children[prereq[i]].push_back(i);
		}

		vector<int> order;
		for (int i = 1; i <= N; i++) {
			if (prereq[i] == 0) order.push_back(i);
		}

		for (int i = 0; i < order.size(); i++) {
			for (int c : children[order[i]]) order.push_back(c);
		}

		height.assign(N + 1, 1);
		for (int i = order.size() - 1; i >= 0; i--) {
			for (int c : children[order[i]]) height[order[i]] = max(height[order[i]], height[c] + 1);
		}

		priority_queue<pair<int, int>> available;
		for (int i = 1; i <= N; i++) {
			if (prereq[i] == 0) available.push({height[i], i});
		}

		int ans = 0;
		for (int sem = 0; sem < M && !available.empty(); sem++) {
			vector<int> taken;
			while (taken.size() < K && !available.empty()) {
				taken.push_back(available.top().second);
				available.pop();
			}

			ans += taken.size();

			for (int course : taken) {
				for (int c : children[course]) available.push({height[c], c});
			}
		}

		cout << ans << "\n";
	}
}
