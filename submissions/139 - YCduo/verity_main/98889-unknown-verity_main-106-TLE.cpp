#include <iostream>
#include <vector>
using namespace std;

/*
 * Print a sequence of guesses until you guess the answer string.
 * You may use the read_string() and print_guess() helper functions defined below.
 *
 * N: Length of the string
 * K: Number of different -ities
 * A: List containing the different -ities
 */

string theString = "";

/*
 * Reads a single string from standard input.
 */
string read_string() {
    string s; cin >> s;
    return s;
}

/*
 * Prints a guess to standard output and flushes the output stream buffer.
 */
string print_guess(string guess) {
    cout << guess << endl;
}

void solve(int N, int K, vector<char>& A) {
    for (int i = 0; i < 1003; i++){
        string output = read_string();

        if (output == "CORRECT") {
            return;
        } else {
            theString = output;

            for (int i = 0; i < N; i++) {
                if (theString[i] == '_') theString[i] = A[0];
            }

            theString.erase(0,1);
            
            print_guess(theString);
        }
    }
}

int main() {
    int T;
    cin >> T;
    
    for (int i = 0; i < T; i++) {
        int N, K;
        cin >> N >> K;

        vector<char> A(K);
        for (int j = 0; j < K; j++) {
            cin >> A[j];
        }

        for (int j = 0; j < N; j++) {
            theString.push_back(A[0]);
        }

        solve(N, K, A);
    }

    return 0;
}
