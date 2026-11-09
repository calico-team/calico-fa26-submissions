#include <iostream>
#include <vector>
using namespace std;
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
    string ans = ""; ans.resize(N, ' ');
    for (int i = 0; i < 26; i++) {
        string s = "";
        for (int j = 0; j < N; j++) {
            s.push_back('A' + i);
        }
        print_guess(s);
        string temp = read_string();
        if (temp == "CORRECT") return;
        else {
            for (int j = 0; j < temp.length(); j++) {
                if (temp[j] != '_') ans[j] = temp[j];
            }
        }
    }
    print_guess(ans);
}

/*
 * Reads a single string from standard input.
 */


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
