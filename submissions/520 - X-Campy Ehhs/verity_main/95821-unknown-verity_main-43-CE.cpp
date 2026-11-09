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
    string guess (N, A[0]);
    vector<int> nextLetterIndex(N, 0);
    while (true) {
        print_guess(guess);
        string response = read_string();

        if (response == "correct") {
            return ;
        }

        for (int i = 0; i < N; i++) {
            if (response[i] = '_') {
                nextLetterIndex[i] = nextLetterIndex[i] + 1;
                guess[i] = A[nextLetterIndex[i]];
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
