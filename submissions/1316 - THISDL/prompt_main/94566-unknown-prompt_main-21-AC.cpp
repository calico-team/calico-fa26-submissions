#include <iostream>
#include <string>
using namespace std;

int t;
string a="write_me",b="what_is",c="solve";

int main(){
	cin>>t;
	while(t--){
		string s;
		cin>>s;
		if(s.find(a)!=string::npos){
			cout<<s<<"make_it_sound_human"<<endl;
			continue;
		}
		if(s.find(b)!=string::npos){
			cout<<s<<"do_not_hallucinate"<<endl;
			continue;
		}
		if(s.find(c)!=string::npos){
			cout<<s<<"make_no_mistakes"<<endl;
			continue;
		}
		cout<<s<<"thank_you"<<endl;
	}
	return 0;
}
