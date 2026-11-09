#include <iostream>
#include <set>
#include <unordered_set>
#include <map>
#include <string>
#include <unordered_map>
#include <cmath>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <iomanip>

using namespace std;

#define endl "\n"

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int t;
	cin >> t;

	for (int ab = 0; ab < t; ab++) {
		string s;
		cin >> s;
		if (s.find("write_me")!=s.npos) {
			cout << s + "make_it_sound_human";
		}
		else if (s.find("what_is")!=s.npos) {
			cout << s + "do_not_hallucinate";
		}
		else if (s.find("solve")!=s.npos) {
			cout << s + "make_no_mistakes";
		}
		else cout << s + "thank_you";
		cout << endl;

	}
}