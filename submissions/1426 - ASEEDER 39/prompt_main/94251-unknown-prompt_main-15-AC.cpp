#include<bits/stdc++.h>
using namespace std;
string s;
int n,len;
int main(){
	std::string a="write_me";
	std::string b="what_is";
	std::string c="solve";
		cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		if(s.find(a)!=std::string::npos){
			cout<<s<<"make_it_sound_human"<<endl;
            continue;		
		}
		if(s.find(b)!=std::string::npos){
			cout<<s<<"do_not_hallucinate"<<endl;
			continue;
		}
		if(s.find(c)!=std::string::npos){
			cout<<s<<"make_no_mistakes"<<endl;
			continue;	
		}
		cout<<s<<"thank_you"<<endl;
	}
	return 0;
}