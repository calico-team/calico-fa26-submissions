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
    string current_guess(N, A[0]);
    
    print_guess(current_guess);
    string result = read_string();
    if (result == "CORRECT") return;

    for (int i = 0; i < N; i++) {
        if (result[i] != '_') {
            current_guess[i] = result[i];
            continue;
        }
        
        for (int j = 0; j < K; j++) {
            current_guess[i] = A[j];
            print_guess(current_guess);
            string res = read_string();
            
            if (res == "CORRECT") return;
            
            if (res[i] != '_') {
                current_guess[i] = res[i];
                break; 
            }
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