#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <numeric>
#include <climits>
#include <string>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;

    while (t--) {
        string s;
        cin >> s;
        if (s.find("write_me") != string::npos) {
            s.append("make_it_sound_human");
        } else if (s.find("what_is") != string::npos) {
            s.append("do_not_hallucinate");
        } else if (s.find("solve") != string::npos) {
            s.append("make_no_mistakes");
        } else {
            s.append("thank_you");
        }
        cout << s << "\n";
    }


}