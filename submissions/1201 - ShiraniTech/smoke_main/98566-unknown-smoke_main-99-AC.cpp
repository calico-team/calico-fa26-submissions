#include<iostream>
#include<deque>
using namespace std;
bool solve(int n, long long r, const long long* a){
	int charges=2;
	deque<long long> q;
	for(int i=0; i<n; i++){
		long long t=a[i];
		while(!q.empty() && q.front()<=t){
			q.pop_front();
			charges++;
		}
		if(charges==0) return false;
		charges--;
		long long done=q.empty()? t + r: q.back()+r;
		q.push_back(done);
	}
	return true;
}
int  main(){
int t;
cin>>t;
while(t--){
int n;
long long r;
cin>>n>>r;
long long a[100005];
for(int i=0; i<n; i++) cin>>a[i];
cout<<(solve(n, r, a)? "YES": "NO")<<"\n";
}
  return 0;
}