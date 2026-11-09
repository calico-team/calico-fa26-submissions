#include <iostream>
#include <string>
using namespace std;

const int MAXK=30,MAXN=110;
int t,n,k;
char a[MAXK],ans[MAXN];
bool f[MAXN];

int main(){
	cin>>t;
	while(t--){
		cin>>n>>k;
		for(int i=1;i<=k;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			f[i]=0;
			ans[i]=a[1];
		}
		int num=1;
		while(1){
			for(int i=1;i<=n;i++){
				if(f[i]==0){
					ans[i]=a[num];
				}
				cout<<ans[i];
			}
			cout<<endl;
			string s;
			cin>>s;
			if(s=="CORRECT"){
				break;
			}
			for(int i=0;i<n;i++){
				if(s[i]=='_'){
					continue;
				}
				else{
					f[i+1]=1;
				}
			}
			num++;
		}
	}
	return 0;
}
