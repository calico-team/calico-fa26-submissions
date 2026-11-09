#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<int> adj[200005];
int arr[200005], frek[200005], mod = 998244353;
bool vis[200005];
vector<int> v;


signed main() {
	ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	string sam;
	cin >> sam;
	if(sam == "FIRST") {
		int n;
		cin >> n;
		for(int i = 1; i <= n; i++) arr[i] = 0;
		for(int i = 1; i < n; i++) {
			int a, b;
			cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
			frek[a]++;
			frek[b]++;
		}
		queue<int> q;
		for(int i = 1; i <= n; i++) {
			if(frek[i] == 1) q.push(i);
		}
		int kur = 1;
		for(int i = 1; i < n; i++) {
			int a = q.front();
			q.pop();
			vis[a] = true;
			for(int j = 0; j < adj[a].size(); j++) {
				int b = adj[a][j];
				if(vis[b]) continue;
				arr[a] = a * b;
				kur *= arr[a];
				kur %= mod;
				frek[b]--;
				if(frek[b] == 1) q.push(b);
			}
		}
		for(int i = 1; i <= n; i++) {
			if(arr[i] == 0) {
				arr[i] = (kur + 1) * -1;
			}
			cout << arr[i] << " ";
		}
		cout << "\n";
	} else {
		int n;
		cin >> n;
		int sim, mun = 0, tot = 1;
		vector<pair<int, int>> jaw;
		for(int i = 1; i <= n; i++) {
			cin >> arr[i];
			if(arr[i] == -1) {
				sim = i;
				tot *= i;
			} else if(arr[i] < 0) {
				mun = (arr[i] * -1) - 1;
			} else {
				jaw.push_back({i, arr[i] / i});
				tot *= arr[i];
				tot %= mod;
				v.push_back(arr[i] / i);
			}
		}
		sort(v.begin(), v.end());
		if(v.size() != n - 1) {
			for(int i = 1; i <= n; i++) {
				int a = tot * i;
				a %= mod;
				if(a == mun) {
					jaw.push_back({sim, i});
				}
			}
		}
		for(int i = 0; i < jaw.size(); i++) {
			cout << jaw[i].first << " " << jaw[i].second << "\n";
		}
		
	}
	
}

