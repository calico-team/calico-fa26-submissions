#include <iostream>

using namespace std;

/*
 * Output the result of adding a certain string to the end of a prompt.
 *
 * S: Original prompt
 */

const string a = "write_me";
const string b = "what_is";
const string c = "solve";
string solve(string S) {
	bool flag = 0;
	int i;
	if(S.find(a) != string::npos){
		S+="make_it_sound_human";
	    flag = true;
	}
	if(S.find(b) != string::npos){
		S+="do_not_hallucinate";
		flag = true;
	}
	if(S.find(c) != string::npos) {
		S+="make_no_mistakes";
		flag = true;	
	}
	if(!flag)
	{
		S+="thank_you";
	}
	return S;	
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        string S;
        cin >> S;
        cout << solve(S) << '\n';
    }
}

