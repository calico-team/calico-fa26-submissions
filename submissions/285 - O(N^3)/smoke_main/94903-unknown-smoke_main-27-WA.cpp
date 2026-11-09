
#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	bool istrue;
	int q;cin >> q;
	vector<int>v1;
	for (int i = 0; i < q; i++)
	{
		istrue = true;
		int n,r;cin >> n >> r;
		for (int j = 0; j < n; j++)
		{
			int inpi;cin >> inpi;
			v1.push_back(inpi);
		}
		
		for (int j = 1; j < n; j++)
		{
			if(v1[j]-v1[j-1] < r){
				istrue = false;
			}
		}
		
		if(istrue){
			cout<< "YES" << endl;
		}else{
			cout << "NO" << endl;
		}
		
		v1.clear();
	}
	
	
	
	return 0;
}
