#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    string str; cin >> str;
    ll has1 = 0, has2 = 0, has3 = 0, x = 0, in = 0;
    string s1 = "write_me", s2 = "what_is", s3 = "solve";
    for (ll i = 0; i < str.size(); i++) {
        if (str[i] == 'w' && str.size()-i >= 8) {
            ll x1 = 1, in = 0;
            for (ll j = i; j < i+8; j++) 
                if (str[j] != s1[in++]) x1 = 0;
            if (x1) has1 = 1;
        } if (str[i] == 'w' && str.size()-i >= 7) {
            ll x2 = 1, in = 0;
            for (ll j = i; j < i+7; j++) 
                if (str[j] != s2[in++]) x2 = 0;
            if (x2) has2 = 1;
        } if (str[i] == 's' && str.size()-i >= 5) {
            ll x3 = 1, in = 0;
            for (ll j = i; j < i+5; j++) 
                if (str[j] != s3[in++]) x3 = 0;
            if (x3) has3 = 1;
        }
    } if (!has1 && !has2 && !has3) 
        cout << str << "thank_you" << endl;
    else if (has1)
        cout << str << "make_it_sound_human" << endl;
    else if (has2)
        cout << str << "do_not_hallucinate" << endl;
    else if (has3) 
        cout << str << "make_no_mistakes" << endl;
    return;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll T; cin >> T; while (T--) solve();
    return 0;
}