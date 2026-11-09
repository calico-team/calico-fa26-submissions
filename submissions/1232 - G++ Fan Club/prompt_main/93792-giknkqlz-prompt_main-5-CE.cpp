#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <bit>
#include <map>
#include <set>
#include <deque>
using namespace std;
using ull = unsigned long long;
void solve() {
    string s;
    cin >> s;
    cout << s;
    if (s.contains("write_me")) cout << "make_it_sound_human";
    else if (s.contains("what_is")) cout << "do_not_hallucinate";
    else if (s.contains("solve")) cout << "make_no_mistakes";
    else cout << "thank_you";
    cout << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}