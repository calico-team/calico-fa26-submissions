#include <iostream>
#include <vector>
using namespace std;

// skip cells that a later earthquake already filled
int find_next(vector<int>& next, int x) {
	while (next[x] != x) {
		next[x] = next[next[x]];
		x = next[x];
	}
	return x;
}

/**
 * Return the reading of every seismometer after all Q earthquakes have
 * occurred: an N by M grid of integers, where each reading is the shock
 * level of the most recent earthquake that reached that block (0 if no
 * earthquake reached it).
 *
 * N: the number of rows of blocks
 * M: the number of columns of blocks
 * Q: the number of earthquakes
 * X: the row of the epicenter of the i-th earthquake, in occurrence order
 * Y: the column of the epicenter of the i-th earthquake, in occurrence order
 * P: the power of the i-th earthquake, in occurrence order
 */
vector<vector<int>> solve(int N, int M, int Q, vector<int>& X, vector<int>& Y, vector<int>& P) {
	vector<vector<int>> answer(N, vector<int>(M, 0));
	int stride = M + 1;
	vector<int> next(N * stride);
	for (int i = 0; i < N * stride; i++) next[i] = i;

	// work backwards so each cell only needs its last earthquake
	for (int i = Q - 1; i >= 0; i--) {
		int radius = P[i];
		int square = radius * radius;
		int width = radius;

		for (int offset = 0; offset <= radius; offset++) {
			// the circle gets narrower farther from the center
			while (width * width + offset * offset > square) width--;

			auto fill_row = [&](int row) {
				int start = row * stride;
				int right = start + Y[i] + width;
				int cell = find_next(next, start + Y[i] - width);
				while (cell <= right) {
					int column = cell - start;
					int distance = column - Y[i];
					answer[row][column] = square - offset * offset - distance * distance + 1;
					next[cell] = find_next(next, cell + 1);
					cell = next[cell];
				}
			};

			fill_row(X[i] + offset);
			if (offset != 0) fill_row(X[i] - offset);
		}
	}
	return answer;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T; cin >> T;
	while (T--) {
		int N, M, Q; cin >> N >> M >> Q;
		vector<int> X(Q), Y(Q), P(Q);
		for (int i = 0; i < Q; i++) {
			cin >> X[i] >> Y[i] >> P[i];
		}
		vector<vector<int>> answer = solve(N, M, Q, X, Y, P);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (j > 0) cout << ' ';
				cout << answer[i][j];
			}
			cout << '\n';
		}
	}
	return 0;
}
