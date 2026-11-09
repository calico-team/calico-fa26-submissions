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

vector<pair<long long, long long>> dir = { {0,1},{1,0},{-1,0},{0,-1} };

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	long long t;
	cin >> t;
	for (long long ab = 0; ab < t; ab++) {
		long long n, m, q;
		cin >> n >> m >> q;


		vector<vector<long long>> graph(n, vector<long long>(m,0));
		vector<pair<long long, pair<long long, long long>>> time(q);
		for (long long x = 0; x < q; x++) {
			long long a, b, c;
			cin >> a >> b >> c;
			time[x] = { a,{b,c} };
		}

		vector<vector<long long>> visited(n, vector<long long>(m, -1));

		for (long long x = q - 1; x >= 0; x--) {
			long long a = time[x].first;
			long long b = time[x].second.first;
			long long c = time[x].second.second;
			queue<pair<long long, long long>> que;
			que.push({ a,b });
			visited[a][b] = x;
			while (!que.empty()) {
				long long l = que.front().first;
				long long r = que.front().second;
				que.pop();
				if ((c * c - ((l - a) * (l - a) + (b - r) * (b - r)) + 1) <= 0) continue;
				if (graph[l][r] == 0) graph[l][r] = c * c - ((l - a) * (l - a) + (b - r) * (b - r)) + 1;
				for (auto it : dir) {
					long long newx = l + it.first;
					long long newy = r + it.second;
					if ((newx >= 0 && newx < n) && (newy >= 0 && newy < m)) {
						if (visited[newx][newy] == x) continue;
						visited[newx][newy] = x;
						que.push({ newx,newy });
					}
				}
			}
		}

		for (long long x = 0; x < n; x++) {
			for (long long y = 0; y < m; y++) {
				cout << graph[x][y] << " ";
			}
			cout << endl;
		}
		
		cout << endl;
	}
}