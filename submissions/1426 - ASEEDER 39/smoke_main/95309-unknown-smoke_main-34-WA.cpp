#include<bits/stdc++.h>
using namespace std;
int t,n,r;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d %d",&n,&r);
		int a[100005];
		for(int i=0;i<n;i++){
			scanf("%d",&a[i]);
		}
		int q[2];
		int head=0,tail=0;
		int charges=2;
		int ans=1;
		for(int i=0;i<n;i++){
			if(tail>head&&a[i]-q[head%2]>=r){
				head++;
				charges++;
			}
			if(charges>0){
				charges--;
				q[tail%2]=a[i];
				tail++;
			}else{
				ans=0;
				break;
			}
		}
		if(ans){
			printf("YES\n");
		}else{
			printf("NO\n");
		}
	}
	return 0;
}