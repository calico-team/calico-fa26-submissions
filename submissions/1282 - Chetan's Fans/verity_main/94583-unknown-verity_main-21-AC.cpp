#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    if (!(cin >> tests)) return 0;
    while (tests--) {
        int length, count;
        cin >> length >> count;
        string alphabet(count, ' ');
        for (char& letter : alphabet) cin >> letter;

        string known(length, '_');
        for (char letter : alphabet) {
            string guess = known;
            for (char& position : guess)
                if (position == '_') position = letter;

            cout << guess << endl;
            if (!(cin >> known)) return 0;
            if (known == "CORRECT") break;
        }
    }
}
