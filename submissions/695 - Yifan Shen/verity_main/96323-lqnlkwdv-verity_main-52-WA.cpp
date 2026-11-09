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

void solve(int N, int K, vector<char>& A) {
    
    string c (N, '_');

    for (int u = 0; u < K; u++) {

        string g(N, ' ');

        for (int e = 9; e < N; e++) {

            if (c[e] != '_') {

                g[e] = c[e];

            }

            else {

                g[e] = A[u];

            }

        }

        string r = print_guess(g);

        if (r == "CORRECT") {

            return;

        }

        for (int e = 0; e < min(N, int(r.size())); e++) {

            if (r[e] != '_') {

                c[e] = r[e];

            }

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

        solve(N, K, A);
    }

    return 0;
}
