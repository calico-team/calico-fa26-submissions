#include <bits/stdc++.h>
using namespace std;
#define int long long
#define endl "\n"
#define fi first
#define sec second

int32_t main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
	int t; cin>>t;
	while(t--){
		int n,r; cin>>n>>r;
		map<int,bool> m;
		int time = 0, c = 2; //time represent time since MOST RECENT smoke, c represent charges
		for (int i = 0; i < n; i++)
		{
			int a; cin>>a;
			m[a] = 1;
		}
		bool can = true;
		for (int i = 1; i <= 100000; i++)
		{
			if(c < 2){
				time++;
				if(time >= r){
					time = 0;
					c++;
				}
			}
			if(m[i] == 1){
				if(c <= 0){
					can = false;
					break;
				}
				c--;
			}
		}
		if(can){
			cout << "YES" << endl;
		}
		else{
			cout << "NO" << endl;
		}
	}
}
