#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
#include <numeric>
#include <queue>
#include <stack>
#include <iomanip>
#include <array>
#include <functional>
#include <bitset>
using namespace std;

void baseIO(string s = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if (s.size()) {
        freopen((s + ".in").c_str(), "r", stdin);
        freopen((s + ".out").c_str(), "w", stdout);
    }
}

int subcount = 376;

#define ll long long
#define db long double
#define all(x) (x).begin(), (x).end()

void solve() {
    string s;
    cin >> s;

    if (s.find("write_me") != string::npos) s += "make_it_sound_human";
    else if (s.find("what_is") != string::npos) s += "do_not_hallucinate";
    else if (s.find("solve") != string::npos) s += "make_no_mistakes";
    else s += "thank_you";

    cout << s;
}

signed main() {
    baseIO();

    int t;
    cin >> t;
    while (t--){
        solve(), cout << endl;
    }

    return 0;
}