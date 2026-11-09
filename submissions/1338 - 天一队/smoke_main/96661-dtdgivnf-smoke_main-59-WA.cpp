#include<bits/stdc++.h>
#define randint rand()*rand()+rand()*rand()
#define lowbit(x) (x&(-x))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef double db;
typedef __int128 i128;
typedef unsigned __int128 u128;
ll a[1145140];
int main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--){
		int n,r;
		cin>>n>>r;
		for(int i=1;i<=n;i++)cin>>a[i];
		
		ll r1=0,r2=0;
		bool f=true;
		for(int i=1;i<=n&&f;i++){
			ll tm=a[i]-a[i-1];
			if(r1>0){
				ll tmp=min(r1,tm);
				r1-=tmp;tm-=tmp;
			}
			if(r2>0){
				ll tmp=min(r2,tm);
				r2-=tmp;tm-=tmp;
			}
			
			if(r1==0)r1=r;
			else if(r2==0)r2=r;
			else f=false;
		}
		cout<<(f?"YES":"NO")<<'\n';
	}
	return 0;
}

