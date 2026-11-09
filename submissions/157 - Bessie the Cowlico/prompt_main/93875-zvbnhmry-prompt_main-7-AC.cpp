#include<bits/stdc++.h>
using namespace std;
using LL = long long;
using str = string;
LL n;

int main() {
    // freopen("usaco.in", "r", stdin);
    // freopen("usaco.out", "w", stdout);
    cin >> n;
    while (n--) {
        str in;
        cin >> in;
        if (in.find("write_me") != string::npos) {
            cout << in << "make_it_sound_human\n";
        }
        else if (in.find("what_is") != string::npos) {
            cout << in << "do_not_hallucinate\n";
        }
        else if (in.find("solve") != string::npos) {
            cout << in << "make_no_mistakes\n";
        } else {
            cout << in << "thank_you\n";
        }
    }
}