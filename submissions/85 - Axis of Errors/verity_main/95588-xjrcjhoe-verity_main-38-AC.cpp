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
    string final_guess(N, '.');
    for (char c : A) {
        string guess(N, c);
        print_guess(guess);
        string ans = read_string();
        if (ans == "CORRECT") return;
        for (int i = 0; i < ans.size(); i++) {
            if (ans[i] != '_') final_guess[i] = ans[i];
        }
    }
    print_guess(final_guess);
    read_string();
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
