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
}
