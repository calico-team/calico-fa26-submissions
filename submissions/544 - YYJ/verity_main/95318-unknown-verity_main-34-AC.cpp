#include <iostream>
#include <vector>
using namespace std;

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

/*
 * Print a sequence of guesses until you guess the answer string.
 * You may use the read_string() and print_guess() helper functions defined below.
 *
 * N: Length of the string
 * K: Number of different -ities
 * A: List containing the different -ities
 */
void solve(int N, int K, vector<char>& A) {
    string build;
    for(int i = 0; i < N; i++) build.push_back('_');

    for(int i = 0; i < K; i++){
        string prev = build;
        for(int j = 0; j < N; j++) if(prev[j] == '_') prev[j] = A[i];
        print_guess(prev);
        string inp = read_string();
        if(inp == "CORRECT") return;
        for(int j = 0; j < N; j++){
            if(inp[j] != '_') build[j] = inp[j];
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
