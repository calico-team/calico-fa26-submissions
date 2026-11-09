#include <bits/stdc++.h>
using namespace std;
typedef long long li;
#define fastio ios_base::sync_with_stdio(false);cin.tie(0)
void setIO(string s) {freopen((s + ".in").c_str(), "r", stdin);freopen((s + ".out").c_str(), "w", stdout);}
li mod(li a,li b){li c=a%b;return c<0?c+b:c;}

/*
 * Output the result of adding a certain string to the end of a prompt.
 *
 * S: Original prompt
 */
string solve(string S) {
    if (S.find("write_me") != string::npos) return S.append("make_it_sound_human");
    if (S.find("what_is") != string::npos) return S.append("do_not_hallucinate");
    if (S.find("solve") != string::npos) return S.append("make_no_mistakes");
    return S.append("thank_you");
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        string S;
        cin >> S;
        cout << solve(S) << '\n';
    }
}