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
			if(c < 2){
				if(i == 0)
					time += a[i];
				else
					time += a[i] - a[i-1];
				//cout << "Time elapsed at i = " << i << ": " << time << endl;
				if(time >= r){
					c++;
					time = 0;
				}
			}
			if(c <= 0){
				can = false;
				break;
			}
			else{
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
