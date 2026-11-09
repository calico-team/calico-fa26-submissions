#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
	string s;
	int n;
	cin>>n;
	while(n--){
		cin>>s;
		int f=0;
		for(int i=0;i<s.size();i++){
			for(int len=1;i+len-1<s.size();len++){
				string x=s.substr(i,len);
				if(x=="write_me") f=1,cout<<s<<"make_it_sound_human\n";
				if(x=="what_is") f=1,cout<<s<<"do_not_hallucinate\n";
				if(x=="solve") f=1,cout<<s<<"make_no_mistakes\n";
			}
		}
		if(f==0){
			cout<<s<<"thank_you\n";
		}
	}
}
