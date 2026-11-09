#include<bits/stdc++.h>
using namespace std;

int main(){
	int na;
	cin>>na;
	vector<char> c;
	for(int i=0;i<na;i++){
		int n,k;
		c=vector<char>(k+1,'0');
		string s;
		cin>>n>>k;
		for(int j=0;j<k;j++){
			cin>>c[j];
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
	}
	return 0;
}
