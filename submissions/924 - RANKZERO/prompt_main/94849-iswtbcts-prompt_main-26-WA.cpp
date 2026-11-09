#include <bits/stdc++.h>
using namespace std;

 int main () {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	string s;
	int t;
	cin>>t;
	while(t--){
		cin>>s;
		if (s=="write_me"){
			cout<<s<<"make_it_sound_human\n";
		} else if(s=="what_is"){
			cout<<s<<"do_not_hallucinate\n";
		} else if(s=="solve"){
			cout<<s<<"make_no_mistakes\n";
		} else {
			cout<<"thank_you\n";
		}
	}
	
	return 0;
 }
