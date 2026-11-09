#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,m,a[100001];
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	ll t;
	cin>>t;
	while(t--){
		cin>>n>>m;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		bool pd=1;
		ll ja=1,jb=1,la=0,lb=0;
		for(int i=1;i<=n;i++){
			if(ja==1&&jb==0){
				swap(ja,jb);
				swap(la,lb);
			}
			if(ja==1){
				ja=0;la=m;
			}
			else if(jb==1){
				jb=0;lb=m;
			}
			else{
				pd=0;
				break;
			}
			if(i==n)break;
			ll jt=a[i+1]-a[i],jd;
			if(ja==0){
				jd=la;
				la=max(0ll,la-max(jt,jt-jd));
				jd-=la;
				jt-=jd;
				if(la==0)ja=1;
			}
			if(ja==1&&jb==0){
				jd=lb;
				lb=max(lb-max(jt,jt-jd),0ll);
				jd=jd-lb;
				jt-=jd;
				if(lb==0)jb=1;
			}
		}
		if(pd)cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
	} 
	return 0;
} 
