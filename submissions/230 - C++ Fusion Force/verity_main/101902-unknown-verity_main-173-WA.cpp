#include <iostream>
#include <vector>
using namespace std;

string read_string();
void print_guess(string guess);
/*
 * Print a sequence of guesses until you guess the answer string.
 * You may use the read_string() and print_guess() helper functions defined below.
 *
 * N: Length of the string
 * K: Number of different -ities
 * A: List containing the different -ities
 */
void solve(int N, int K, vector<char>& A) {
    string ans = "";
    for (size_t i = 0; i < N; i++) ans += '_';
    string s = "";
    for (int i = 0; i < K; i++) {
        s = "";
        for (int j = 0; j < K; j++) s += A[i];
        print_guess(s);
        s = read_string();
        cout << s << endl;
        for (size_t j = 0; j < s.size(); j++) {
            if (s[j] != '_') ans[j] = s[j];
        }
    }
    if (s != "CORRECT") {
        print_guess(ans);
        read_string();
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
