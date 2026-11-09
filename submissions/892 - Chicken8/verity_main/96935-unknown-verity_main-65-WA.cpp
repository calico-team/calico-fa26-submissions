#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
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
/*
 * Print a sequence of guesses until you guess the answer string.
 * You may use the read_string() and print_guess() helper functions defined below.
 *
 * N: Length of the string
 * K: Number of different -ities
 * A: List containing the different -ities
 */

void solve(int N, int K, vector<char>& A) {
    // YOUR CODE HERE
    int mark[105];
    memset(mark, 0, sizeof(mark)); 
    
    vector<char> current_guess(N, A[0]);

    while (true) {
        vector<int> pos;
        vector<char> vals;
        for (int i = 0; i < N; i++) {
            if (mark[i] == 0) {
                pos.push_back(i);
                vals.push_back(current_guess[i]);
            }
        }

        if (!vals.empty()) {
            char last = vals.back();
            for (int i = vals.size() - 1; i > 0; i--) {
                vals[i] = vals[i - 1];
            }
            vals[0] = last;
        }

        for (int i = 0; i < pos.size(); i++) {
            current_guess[pos[i]] = vals[i];
        }
        
        // submit
        string s(current_guess.begin(), current_guess.end());
        print_guess(s);
        string result = read_string();
        if (result == "CORRECT") return;
        
        for (int i = 0; i < result.length(); i++) {
            if (result[i] != '_') mark[i] = 1;
        }
    }
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