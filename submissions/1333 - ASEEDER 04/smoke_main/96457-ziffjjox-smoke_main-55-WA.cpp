#include<bits/stdc++.h>
using namespace std;
int main(){
	int T;
	cin >> T;
	while(T--){
		int n,r;
		cin >> n >> r;
		int a[n];
		bool t = true;
		for(int i = 0; i < n; i ++){
			cin >> a[i];
		}
		for(int i = 1; i < n; i ++){
			if(a[i] - a[i-1] < r){
				t = false;
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
