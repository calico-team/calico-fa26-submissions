#include <iostream>
using namespace std;

const int MAXN=100010;
int t,n,r;
long long a[MAXN];

int main(){
	cin>>t;
	while(t--){
		cin>>n>>r;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		long long x=1,y=1;
		bool f=0;
		for(int i=1;i<=n;i++){
			if(a[i]>=x){
				if(y<a[i]){
					x=a[i]+r;
				}
				else{
					x=y+1+r;
				}
			}
			else if(a[i]>=y){
				if(x<a[i]){
					y=a[i]+r;
				}
				else{
					y=x+1+r;
				}
			}
			else{
				f=1;
				cout<<"NO"<<endl;
				break;
			}
		}
		if(f==0){
			cout<<"YES"<<endl;
		}
	}
	return 0;
}
