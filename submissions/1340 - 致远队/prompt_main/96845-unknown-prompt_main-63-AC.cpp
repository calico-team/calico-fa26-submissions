#include <iostream>
#include <string>

using namespace std;

void solve() {
    string s;
    cin >> s;

    // 检查是否包含特定子串并追加相应的后缀
    if (s.find("write_me") != string::npos) {
        cout << s << "make_it_sound_human" << endl;
    } else if (s.find("what_is") != string::npos) {
        cout << s << "do_not_hallucinate" << endl;
    } else if (s.find("solve") != string::npos) {
        cout << s << "make_no_mistakes" << endl;
    } else {
        cout << s << "thank_you" << endl;
    }
}

int main() {

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
