#include <iostream>
using namespace std;

string solve(string S) {
	if (S.find("write_me") != string::npos){
		return S.append("make_it_sound_human");		
	}
	else if (S.find("what_is") != string::npos){
		return S.append("do_not_hallucinate");
	}
	else if (S.find("solve") != string::npos){
		return S.append("make_no_mistakes");
	}
	else{
		return S.append("thank_you");
	}
	
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
