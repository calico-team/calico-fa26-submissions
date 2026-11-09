#include <iostream>
#include <set>
#include <unordered_set>
#include <map>
#include <string>
#include <unordered_map>
#include <cmath>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <iomanip>

using namespace std;

#define endl "\n"

vector<pair<int, int>> dir = { {0,1},{1,0},{-1,0},{0,-1} };

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t;
	cin >> t;
	for (int ab = 0; ab < t; ab++) {
		int n, m, q;
		cin >> n >> m >> q;


		vector<vector<int>> graph(n, vector<int>(m,0));
		vector<pair<int, pair<int, int>>> time(q);
		for (int x = 0; x < q; x++) {
			int a, b, c;
			cin >> a >> b >> c;
			time[x] = { a,{b,c} };
		}

		vector<vector<int>> visited(n, vector<int>(m, -1));

		for (int x = q - 1; x >= 0; x--) {
			int a = time[x].first;
			int b = time[x].second.first;
			int c = time[x].second.second;
			queue<pair<int, int>> que;
			que.push({ a,b });
			visited[a][b] = x;
			while (!que.empty()) {
				int l = que.front().first;
				int r = que.front().second;
				que.pop();
				if ((c * c - ((l - a) * (l - a) + (b - r) * (b - r)) + 1) <= 0) continue;
				if (graph[l][r] == 0) graph[l][r] = c * c - ((l - a) * (l - a) + (b - r) * (b - r)) + 1;
				for (auto it : dir) {
					int newx = l + it.first;
					int newy = r + it.second;
					if ((newx >= 0 && newx < n) && (newy >= 0 && newy < m)) {
						if (visited[newx][newy] == x) continue;
						visited[newx][newy] = x;
						que.push({ newx,newy });
					}
				}
			}
		}

		for (int x = 0; x < n; x++) {
			for (int y = 0; y < m; y++) {
				cout << graph[x][y] << " ";
			}
			cout << endl;
		}
		
		cout << endl;
	}
}