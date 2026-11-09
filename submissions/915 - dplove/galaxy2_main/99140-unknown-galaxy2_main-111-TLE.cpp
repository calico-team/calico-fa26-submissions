#include <bits/stdc++.h>
#define int long long
using namespace std;

int N, M;
vector<string> grid;
vector<vector<vector<int>>> dist;
vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool oob(int y, int x) {
	if (y < 0 || y >= N) return true;
	if (x < 0 || x >= M) return true;
	return false;
}

bool active(int y, int x, int mode) {
	char tile = grid[y][x];
	if (tile == '.') return true;

	if (mode == 0) return tile == 'B';
	return tile == 'R';
}

void bfs(int startY, int startX) {
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++) {
			dist[y][x][0] = -1;
			dist[y][x][1] = -1;
		}
	}

	queue<array<int, 3>> q;
	dist[startY][startX][0] = 0;
	q.push({startY, startX, 0});

	while (!q.empty()) {
		auto [y, x, mode] = q.front();
		q.pop();

		for (auto [dirY, dirX] : dirs) {
			if (oob(y+dirY, x+dirX)) continue;
			if (!active(y+dirY, x+dirX, mode)) continue;
			if (dist[y+dirY][x+dirX][mode] != -1) continue;

			dist[y+dirY][x+dirX][mode] = dist[y][x][mode] + 1;
			q.push({y+dirY, x+dirX, mode});
		}

		if (grid[y][x] == '.' && dist[y][x][1 - mode] == -1) {
			dist[y][x][1 - mode] = dist[y][x][mode] + 1;
			q.push({y, x, 1 - mode});
		}
	}
}

signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T;
	cin >> T;

	while (T--) {
		int Q;
		cin >> N >> M >> Q;

		grid.assign(N, "");
		for (int i = 0; i < N; i++) cin >> grid[i];

		dist.assign(N, vector<vector<int>>(M, vector<int>(2, -1)));

		while (Q--) {
			int startY, startX, endY, endX, K;
			cin >> startY >> startX >> endY >> endX >> K;

			bfs(startY, startX);

			int best = LLONG_MAX;
			for (int mode = 0; mode < 2; mode++) {
				if (dist[endY][endX][mode] != -1) best = min(best, dist[endY][endX][mode]);
			}

			if (best <= K) {
				cout << "YES" << "\n";
			} else {
				cout << "NO" << "\n";
			}
		}
	}
}
