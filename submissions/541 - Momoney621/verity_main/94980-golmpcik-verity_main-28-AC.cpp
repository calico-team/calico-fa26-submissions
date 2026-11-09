#include <iostream>
#include <string>
using namespace std;

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int len, cnt;
        cin >> len >> cnt;

        string opts = "";
        for (int j = 0; j < cnt; j++) {
            char c;
            cin >> c;
            opts += c;
        }

        string known = "";
        for (int j = 0; j < len; j++) {
            known += '?';
        }

        for (int g = 0; g < cnt; g++) {
            string guess = "";
            for (int j = 0; j < len; j++) {
                if (known[j] == '?') {
                    guess += opts[g];
                } else {
                    guess += known[j];
                }
            }

            cout << guess << endl;

            string res;
            cin >> res;
            if (res == "CORRECT") {
                break;
            }

            for (int j = 0; j < len; j++) {
                if (res[j] != '_') {
                    known[j] = res[j];
                }
            }
        }
    }
}