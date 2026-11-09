#include <bits/stdc++.h>
using namespace std;

 int main () {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int t; cin >> t;
	string s1 = "write_me"; string s2 = "what_is"; string s3 = "solve";
	while(t--){
		string s; cin >> s;
		if(s.find(s1)!=string::npos){
			cout << s << "make_it_sound_human\n";
		} else if(s.find(s2)!=string::npos){
			cout << s << "do_not_hallucinate\n";
		} else if(s.find(s3)!=string::npos){
			cout << s << "make_no_mistakes\n";
		} else {
			cout << s << "thank_you\n";
		}
	}
	return 0;
 }
