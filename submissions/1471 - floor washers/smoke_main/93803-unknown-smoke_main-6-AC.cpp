#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
		int n,m;
		cin >> n >> m;
		int cur=2,nxt=0;
		bool can=true;
		for(int i=0; i<n; i++){
			int x;
			cin >> x;
			while(cur<2&&nxt<=x){
				cur++;
				nxt+=m;
			}
			if(cur<=0) can=false;
			cur--;
			if(cur==1) nxt=x+m;
		}
		if(can) cout << "YES\n";
		else cout << "NO\n";
	}
}
