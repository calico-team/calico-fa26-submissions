#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T; cin >> T;
    while (T--) {
        string S; cin >> S;
        auto Has = [&](const char* p) { return S.find(p) != string::npos; };
        cout << S << (Has("write_me") ? "make_it_sound_human" :
                      Has("what_is")  ? "do_not_hallucinate" :
                      Has("solve")    ? "make_no_mistakes" : "thank_you") << '\n';
    }
}