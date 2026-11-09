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
		ll n,r;
		cin>>n>>r;
		for(int i=1;i<=n;i++)cin>>a[i];
		
		ll rem=r*2;
		bool f=true;
		for(int i=1;i<=n&&f;i++){
			rem=min(rem+a[i]-a[i-1],2*r);
			if(rem>=r)rem-=r;
			else f=false;
		}
		cout<<(f?"YES":"NO")<<'\n';
	}
	return 0;
}
/*
5
5 10
20 30 40 50 60
7 100
1 2 3 4 5 6 7
4 10
1 2 12 13
8 5
5 10 17 30 36 45 50 56
9 30
20 70 80 90 100 190 210 220 250
*/
