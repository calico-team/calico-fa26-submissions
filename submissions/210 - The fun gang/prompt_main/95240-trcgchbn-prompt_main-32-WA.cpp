#include <iostream>
typedef long long ll;
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    // code in word
    string x = "";
    cin >> x;
    ;
    if (x.find("write_me", 0) != -1) {
        x += "_make_it_sound_human";
    }
    else if (x.find(("what_is"), 0) != -1){
        x += "_do_not_hallucinate";
    }
    else if (x.find(("solve"), 0) != -1) {
        x += "_make_no_mistakes";
    }
    else {
        x += "_thank_you";
    }
    cout << x;
    return 0;
}