#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    // code in word
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        string x = "";
        cin >> x;
        ;
        if (x.find("write_me", 0) != -1) {
            x += "make_it_sound_human";
        }
        else if (x.find(("what_is"), 0) != -1){
            x += "do_not_hallucinate";
        }
        else if (x.find(("solve"), 0) != -1) {
            x += "make_no_mistakes";
        }
        else {
            x += "thank_you";
        }
        cout << x << "\n";
    }
    return 0;
}