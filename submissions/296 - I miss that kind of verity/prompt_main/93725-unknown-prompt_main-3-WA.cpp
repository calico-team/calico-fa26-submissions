#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int T;
	cin >> T;
	string line;
	getline(cin, line);
	while (T--) {
		getline(cin, line);
		if (line.find("write_me")) {
			line += "make_it_sound_human";
		}
		else if (line.find("what_is")) {
			line += "do_not_hallucinate";
		}
		else if (line.find("solve")) {
			line += "make_no_mistakes";
		}
		else {
			line += "thank_you";
		}
		cout << line << endl;
	}
}
