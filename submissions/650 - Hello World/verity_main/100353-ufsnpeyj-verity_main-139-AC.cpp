#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;

    for (int test=0; test<t; test++) {
        int n, k;
       cin >> n >> k;

        vector<char> letters(k);
        for( int i =0;i<k; i++) {
       cin >> letters[i];
        }

              string answer(n, '_');

        for (int i= 0; i< k; i++) {
            string guess = answer;

            for (int j =0; j < n;j++ )  {
                 if (guess[j] == '_') {
 

                      guess[j] = letters[i];
                }
            }

            cout << guess << endl;

            string reply;
            if (!(cin >> reply)) return 0;
            if (reply == "CORRECT") break;

            answer = reply;
        }
    }

    return 0;
}