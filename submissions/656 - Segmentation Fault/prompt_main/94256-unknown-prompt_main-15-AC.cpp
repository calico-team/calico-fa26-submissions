#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin >> t;
	cin.ignore();
	while (t--) {
		string s;
		getline(cin, s);
		if (s.find("write_me") != string::npos) {
			cout << s << "make_it_sound_human";
		}
		else if (s.find("what_is") != string::npos) {
			cout << s << "do_not_hallucinate";
		}
		else if (s.find("solve") != string::npos) {
			cout << s << "make_no_mistakes";
		}
		else cout << s << "thank_you";
		cout << '\n';
	}
}