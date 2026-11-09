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
void solve(int N, int K, vector<char>& A) {
    string guess(N, A[0]);
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            if (guess[j] == '_') {
                guess[j] = A[i];
            }
        }
        cout << guess << endl;
        string response;
        cin >> response;
        if (response == "CORRECT") {
            return;
        }
        for (int j = 0; j < N; j++) {
            if (response[j] == '_') {
                guess[j] = '_';
            } else {
                guess[j] = response[j];
            }
        }
    }
}

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

        solve(N, K, A);
    }

    return 0;
}