#include <iostream>
#include <vector>
#include <string>
using namespace std;
string a = "hello";
int i = 1;
string read_string();
string print_guess(string guess);
/*
 * Print a sequence of guesses until you guess the answer string.
 * You may use the read_string() and print_guess() helper functions defined below.
 *
 * N: Length of the string
 * K: Number of different -ities
 * A: List containing the different -ities
 */
void solve(int N, int K, vector<char>& A) { 
    a.assign(N,A[0]);
    print_guess(a);
    a = read_string();
    while(a != "correct" && i<K){
        a.replace(a.begin(),a.end(), '_',A[i]);
        i+=1;
        print_guess(a);
        a = read_string();
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
}
