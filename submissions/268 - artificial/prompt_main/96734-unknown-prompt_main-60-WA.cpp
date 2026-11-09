#include <iostream>
#include <string>

using namespace std;

string solve(string S) {
 
    string result = "make_it_sound_human";
    return S + result;
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
