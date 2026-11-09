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
void solve(int N, int K, vector<char>& A);
string read_string();
void print_guess(string guess);

void solve(int N, int K, vector<char>& A) {
    // Each unknown position tries the next candidate letter every round;
    // positions the judge confirms (non-'_') are locked in.
    string cur(N, '?');
    for (int t = 0; ; t++) {
        string guess(N, 'A');
        for (int i = 0; i < N; i++)
            guess[i] = (cur[i] != '?') ? cur[i] : A[t % K];
        print_guess(guess);
        string res = read_string();
        if (res == "CORRECT") return;
        for (int i = 0; i < N; i++)
            if (res[i] != '_') cur[i] = res[i];
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
void print_guess(string guess) {
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
