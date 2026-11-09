#include<bits/stdc++.h>
using namespace std;

int main(){
	int na;
	char ci;
	cin>>na;
	string c;
	for(int i=0;i<na;i++){
		int n,k;
		c="";
		string s;
		cin>>n>>k;
		for(int j=0;j<k;j++){
			cin>>ci;
			c=c+ci;
		}
		for(int j=0;j<n;j++){
			cout<<c[0];
		}
		cout<<endl;
		for(int j=1;j<k;j++){
			cin>>s;
			if(s=="CORRECT")break;
			for(int q=0;q<n;q++){
				if(s[q]=='_')s[q]=c[j];
			}
			cout<<s<<endl;
		}
		if(s!="CORRECT")cin>>s;
	}
	return 0;
}
