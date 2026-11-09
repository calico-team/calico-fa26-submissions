#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, r;
int a[100005];

void solve(){
	scanf("%d %d", &n, &r);
	for(int i=0; i<n; i++){
		scanf("%d", &a[i]);
	}
	deque<int> dq;
	for(int i=0; i<n; i++){
		while(!dq.empty()&& dq.front() <= a[i]){
			dq.pop_front();
		}
		if(dq.size() == 2){
			printf("NO\n");
			return;
		}
		if(!dq.empty()) dq.push_back(max(a[i], dq.back())+r);
		else dq.push_back(a[i]+r);
	}
	printf("YES\n");
}

int main(){
	int t = 1;
	scanf("%d", &t);
	while(t--) solve();
}