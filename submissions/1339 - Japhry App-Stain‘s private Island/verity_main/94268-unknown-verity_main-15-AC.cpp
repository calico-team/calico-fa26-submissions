#include <bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin>>n;
	for(int i=0;i<n;i++){
		int l,c;
		char cs[26];
		cin>>l>>c;
		for(int j=0;j<c;j++){
			cin>>cs[j];
		}
		char ans[110];
		memset(ans,0,sizeof(ans));
		for(int j=0;j<c;j++){
			for(int k=0;k<l;k++){
				if(ans[k]=='_' || ans[k]==0)ans[k]=cs[j];
			}
			for(int k=0;k<l;k++){
				cout<<ans[k];
			}
			cout<<endl;
			string result;
			cin>>result;
			if(result=="CORRECT")break;
			for(int k=0;k<l;k++){
				ans[k]=result[k];
			}
		}
	}
	return 0;
}
