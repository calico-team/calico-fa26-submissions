#include <bits/stdc++.h>
using namespace std;
#define int long long
string str;
int t;

signed main() {
    cin >> t;
    while (t--) {
        cin >> str;
        if (str.find("write_me") != str.npos) cout << str << "make_it_sound_human" << endl;
        else if (str.find("what_is") != str.npos) cout << str << "do_not_hallucinate" << endl;
        else if (str.find("solve") != str.npos) cout << str << "make_no_mistakes" << endl;
        else cout << str << "thank_you" << endl;
    }
    return 0;
}