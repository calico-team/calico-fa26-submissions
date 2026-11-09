
#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin>>t;
	while(t--) {
		string s;
		cin>>s;
		cout<<s;
		bool c1 = true, c2 = false, c3 = false;
		if(s.find("write_me") + 1) cout<<"make_it_sound_human";
		else if(s.find("what_is") + 1) cout<<"do_not_hallucinate";
		else if(s.find("solve") + 1) cout<<"make_no_mistakes";
		else cout<<"thank_you";
		cout<<endl;
	}
}
