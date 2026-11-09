#include<bits/stdc++.h>
using namespace std;
int T,n;
long long R;
int main(){
	cin>>T;
	while(T--){
		cin>>n>>R;
		int charges=2;
		bool ok=true;
		queue<long long> q;
		for(int i=0;i<n;i++){
			long long t;
			cin>>t;
			if(!ok) continue;
			while(!q.empty()&&q.front()<=t){
				q.pop();
				charges++;
			}
			if(charges==0){
				ok=false;
			}
			else{
				charges--;
				if(q.empty()){
					q.push(t+R);
				}
				else{
					q.push(q.back()+R);
				}
			}
		}
		if(ok) cout<<"YES"<<endl;
		else cout<<"NO"<<endl;
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
12 12 13
8 5
5 10 17 30 36 45 50 56
9 30
20 70 80 90 100 190 210 220 250
*/
