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

		vector<vector<long long>> row(n, vector<long long>(m + 1));
		for (long long x = 0; x < n; x++) {
			for (long long y = 0; y <= m; y++) {
				row[x][y] = y;
			}
		}

		for (long long x = q - 1; x >= 0; x--) {
			long long a = time[x].first;
			long long b = time[x].second.first;
			long long c = time[x].second.second;
			for (long long l = a - c; l <= a + c; l++) {
				long long rem = c * c - (l - a) * (l - a);
				long long w = sqrt(rem);
				long long y = b - w;
				while (y <= b + w) {
					long long root = y;
					while (row[l][root] != root) root = row[l][root];
					while (row[l][y] != root) {
						long long temp = row[l][y];
						row[l][y] = root;
						y = temp;
					}
					y = root;
					if (y > b + w) break;
					graph[l][y] = rem - (y - b) * (y - b) + 1;
					row[l][y] = y + 1;
					y++;
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