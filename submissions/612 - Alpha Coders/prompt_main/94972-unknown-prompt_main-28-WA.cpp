#include<bits/stdc++.h>
using namespace std;

int main(){
	int t;
	cin>>t;
	while(t--){
		string S;
		cin>>S;
		if(S.find("write_me")){
			S+="make_it_sound_human";
		}
		else if(S.find("what_is")){
			S+="do_not_hallucinate";
		}
		else if(S.find("solve")){
			S+="make_no_mistakes";
		}
		else{
			S+="thank_you";
		}
		cout<<S;
	}
}
