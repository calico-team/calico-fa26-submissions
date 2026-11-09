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

string theString = "";

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

    for (int i = 0; i < 1003; i++){
        string output = read_string();

        if (output == "CORRECT") {
            return;
        } else {
            theString = output;

            for (int i = 0; i < N; i++) {
                if (theString[i] == '_') theString[i] = A[0];
            }

            A.erase(A.begin());
            
            print_guess(theString);
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

        //before each try it primes the thing with the initial guess of like "AAAAAA" and gets the first response
        for (int j = 0; j < N; j++) {
            theString.push_back(A[0]);
        }

        cout << theString;
        solve(N, K, A);
    }

    return 0;
}
