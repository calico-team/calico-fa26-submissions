#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl '\n'


signed main() {

    int t;
    cin >> t;
    while (t--){
        int N, k;
		cin >> N >> k;
		int ans = N*k;
		vector<pair<int,int>> e;
		map<int,vector<int>> n; 
		
		while (N--){
			int x, y, z; string d;
			cin >> x >> y >> z >> d;
			if (d == "E"){
				e.push_back({x+y, x});
			} else {
				n[x+y].push_back(x);
			}
		}

		for (auto& [key,a] : n){
			sort(a.begin(), a.end());
		}
		for (int i = 0; i < e.size(); i++){

			if (n.find(e[i].first) != n.end()) {
				auto it1 = lower_bound(n[e[i].first].begin(), n[e[i].first].end(), e[i].second);
				auto it2 = upper_bound(n[e[i].first].begin(), n[e[i].first].end(), e[i].second + k-1);
				ans -= distance(it1, it2);
			}
		}
		
		cout << ans << endl;

        
    }


}