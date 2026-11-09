#include<bits/stdc++.h>
using namespace std;
int T;
string s,a,b,c;
int main(){
	a="write_me";
	b="what_is";
	c="solve";
	cin>>T;
	for(int i=1;i<=T;i++){
		int cnt=0;
		cin>>s;
		int ia=s.find(a);
		if(ia!=string::npos){
			s+="make_it_sound_human";
			cnt=1;
		}
		int ib=s.find(b);
		if(ib!=string::npos){
			s+="do_not_hallucinate";
			cnt=1;
		}
		int ic=s.find(c);
		if(ic!=string::npos){
			s+="make_no_mistakes";
			cnt=1;	
		}
		if(cnt==0){
			s+="thank_you";
		}
		cout<<s<<endl;	
	}
	return 0;	
} 
