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
    // YOUR CODE HERE
    vector<char> answer(N, A[0]);
    string a = "ABC";
    int j=1;
    while (a != "CORRECT") {
        for (auto& i : answer) {
            cout<<i;
        }
        cout<<endl;
        cin >> a;
        for (int i=0; i<N; i++) {
            if (answer[i] != a[i]) {
                answer[i] = A[j];
            }
        }
        j++;
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
