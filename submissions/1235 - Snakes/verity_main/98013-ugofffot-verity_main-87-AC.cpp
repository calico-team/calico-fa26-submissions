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
    string g(N, '?');
    for (char x : A) {
        for (char &c : g) if (c == '?') c = x;
        cout << g << endl;
        string r; cin >> r;
        if (r == "CORRECT") return;
        for (int i = 0; i < N; i++) if (r[i] == '_') g[i] = '?';
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
    ios::sync_with_stdio(0);
    cin.tie(0);
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
