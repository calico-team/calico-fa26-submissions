#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
int main() {
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int x; cin >> x;
    while (x--) {
		string s;
		string append;
		cin >> s;
		if (s.find("write_me") != string::npos) {
			append="make_it_sound_human";
		} else if (s.find("what_is") != string::npos) {
			append="do_not_hallucinate";
		} else if (s.find("solve") != string::npos) {
			append="make_no_mistakes";
		} else {
			append="thank_you";
		}
		cout << s << append << "\n";
	}
}
