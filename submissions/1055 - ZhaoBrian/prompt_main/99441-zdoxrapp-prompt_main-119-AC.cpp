#include <iostream>
#include <string>
using namespace std;

int main() {
	int t;
	cin >> t;
	while(t--) {
		string s;
		cin >> s;
		if(s.find("write_me")!=std::string::npos) 
			s+="make_it_sound_human";
		else if(s.find("what_is")!=std::string::npos)
			s+="do_not_hallucinate";
		else if(s.find("solve")!=std::string::npos)
			s+="make_no_mistakes";
		else
			s+="thank_you";
		cout << s << "\n";
	}
	return 0;
}
