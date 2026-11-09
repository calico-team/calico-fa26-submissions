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
void print_guess(string guess) {
    cout << guess << endl;
    return;
}

void solve(int N, int K, vector<char>& A) {
    // YOUR CODE HERE
    string ans(N, '_');
    for (int i = 0; i < K; i++) {
        string test(N, A[i]);
        print_guess(test);
        string s = read_string();
        if (s == "CORRECT") return;
        for (int j = 0; j < N; j++) {
            if (s[j] != '_') ans[j] = s[j];
        }
    }
    print_guess(ans);
    read_string();
    return;
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
