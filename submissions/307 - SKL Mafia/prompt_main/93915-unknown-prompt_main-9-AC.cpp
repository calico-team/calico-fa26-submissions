#include <iostream>
#include <string>

using namespace std;

void solve(string S);

int main(void) {
	int tc;
	cin >> tc;
	for (int i = 0; i<tc; i++) {
		string S_;
		cin >> S_;
		solve(S_);
	}
}

void solve(string S) {
	string OG = S;
	if (S.find("write_me") != string::npos) {
		S += "make_it_sound_human\n";
	}
	if (S.find("what_is") != string::npos) {
		S += "do_not_hallucinate\n";
	}
	if (S.find("solve") != string::npos) {
		S += "make_no_mistakes\n";
	}
	if (OG == S) {
		S += "thank_you\n";
	}
	cout << S;
	return;
}