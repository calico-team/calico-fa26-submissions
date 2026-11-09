#include <iostream>
#include <algorithm>
#include <string>
using namespace std;


void __(){
	string s; cin>>s;
	if(s.find("write_me")!=string::npos){
		s+="make_it_sound_human";
	}else if(s.find("what_is")!=string::npos){
		s+="what_is_the_day_gta6_comes_out_";
	}else if(s.find("solve")!=string::npos){
		s+="make_no_mistakes";
	}
	else{
		s+="thank_you";
	}
	cout<<s<<endl;
}

int main(){
	int _; cin>>_;
	for(int i = 0; i<_; i++) __();
}