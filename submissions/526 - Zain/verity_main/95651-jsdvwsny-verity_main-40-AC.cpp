
#include <iostream>
#include <string>
using namespace std;

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N, K;
        cin >> N >> K;

        string letters;
        for (int i = 0; i < K; i++) {
            char c;
            cin >> c;
            letters += c;
        }

        string known(N, '_');

        for (char c : letters) {
            string guess = known;

            for (char &ch : guess) {
                if (ch == '_')
                    ch = c;
            }

            cout << guess << endl;

            string response;
            if (!(cin >> response))
                return 0;

            if (response == "CORRECT")
                break;

            known = response;
        }
    }

    return 0;
}
