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
		vector<int> a(n);
		int time = 0, c = 2; //time represent time since MOST RECENT smoke, c represent charges
		for (int i = 0; i < n; i++)
		{
			cin>>a[i];
		}
		bool can = true;
		for (int i = 0; i < n; i++)
		{
			if(c<2){
				time += a[i] - a[i-1];
				if(time >= r){
					c += time/r;
					c = min(2LL, c);
					if(c==2)
						time = 0;
					else
						time -= r * (time/r);
				}
			}
			if(c <= 0){
				can = false;
				break;
			}
			c--;
		}
		
		if(can){
			cout << "YES" << endl;
		}
		else{
			cout << "NO" << endl;
		}
	}
}
