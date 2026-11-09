#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
	// your code goes here
	ll t;
	cin >> t;
	while(t--){
	    string s;
	    cin >> s;
	    if(s.find("write_me") != string::npos){
	        s.append("make_it_sound_human");
	    }
	    else if(s.find("what_is") != string::npos){
	        s.append("do_not_hallucinate");
	    }
	    else if(s.find("solve") != string::npos){
	        s.append("make_no_mistakes");
	    }
	    else{
	        s.append("thank_you");
	    }
	    cout << s << endl;
	}

}
