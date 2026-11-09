#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin >> T;
	while(T--){
		int n,r;
		cin >> n >> r;
		int a[n],sum = 0;
		bool t = true;
		for(int i = 0; i < n; i ++){
			cin >> a[i];
		}
		sum = a[0];
		for(int i = 0; i < n; i ++){
			if(sum > a[i]){
				t = false;
			}
			else{
				sum += r;
				//if(i + 1 != n && sum < a[i+1]){
				//	sum = a[i+1];
				//}
			}
		}
		if(t){
			cout << "YES" << endl;
		}
		else{
			cout << "NO" << endl;
		}
	} 
}
