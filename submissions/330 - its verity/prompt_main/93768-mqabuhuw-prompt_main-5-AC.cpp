#include <bits/stdc++.h>

using namespace std;
#define sz(x) ((int)x.size())
typedef long long ll;
int n, m, k;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    string s;
    while (n --) {
        cin >> s;
        if (s.find("write_me") != string::npos) cout << s << "make_it_sound_human";
        else if (s.find("what_is") != string::npos) cout << s << "do_not_hallucinate";
        else if (s.find("solve") != string::npos) cout << s << "make_no_mistakes";
        else cout << s << "thank_you";
        cout << "\n";
    }
    return 0;
}
