#include <bits/stdc++.h>
using namespace std;
#define int long long
template<class T> inline void setmax(T& a, T b) {if (a < b) a = b;}
template<class T> inline void setmin(T& a, T b) {if (a > b) a = b;}
signed main() {
    int t = 1;
    cin >> t;
    while (t--) {
        string a;
        cin >> a;
        if (a.find("write_me") != string::npos) {
            a += "make_it_sound_human";
        }
        else if (a.find("what_is") != string::npos) {
            a += "do_not_hallucinate";
        }
        else if (a.find("solve") != string::npos) {
            a += "make_no_mistakes";
        }
        else a += "thank_you";
        cout << a << endl;
    }
}