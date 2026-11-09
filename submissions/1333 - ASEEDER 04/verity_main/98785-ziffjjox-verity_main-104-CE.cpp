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
    string final_ans(N, '_');
    for (int i = 0; i < K - 1; i++) {
        char current_char = A[i];
        string current_guess = "";
        for (int j = 0; j < N; j++) {
            if (final_ans[j] == '_') {
                current_guess += current_char;
            } else {
                current_guess += final_ans[j];
            }
        }
        string response = print_guess(current_guess);
        if (response == "CORRECT") {
            return;
        }
        for (int j = 0; j < N; j++) {
            if (response[j] != '_') {
                final_ans[j] = response[j];
            }
        }
    }
    for (int j = 0; j < N; j++) {
        if (final_ans[j] == '_') {
            final_ans[j] = A[K - 1];
        }
    }
    print_guess(final_ans);
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
    return read_string();
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
