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
		queue<pair<int, int>> que;
		vector<pair<int, pair<int, int>>> time(q);
		for (int x = 0; x < q; x++) {
			int a, b, c;
			cin >> a >> b >> c;
			time[x] = { a,{b,c} };
		}

		for (int x = q - 1; x >= 0; x--) {
			int a = time[x].first;
			int b = time[x].second.first;
			int c = time[x].second.second;
			que.push({ a,b });
			while (!que.empty()) {
				int l = que.front().first;
				int r = que.front().second;
				que.pop();
				if ((c * c - ((l - a) * (l - a) + (b - r) * (b - r)) + 1) < 0) continue;
				graph[l][r] = c * c - ((l - a) * (l - a) + (b - r) * (b - r)) + 1;
				for (auto it : dir) {
					int newx = l + it.first;
					int newy = r + it.second;
					if ((newx >= 0 && newx < n) && (newy >= 0 && newy < m)) {
						if (graph[newx][newy] != 0) continue;
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