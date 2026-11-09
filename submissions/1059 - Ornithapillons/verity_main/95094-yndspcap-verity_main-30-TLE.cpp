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
    int x = 0;
    vector<char> sol(K);
    vector<bool> rght(K);
    while ( x == 0){
        for (int h = 0; h < A.size(); h++){
            if (!rght[h]){
                sol[h] = A[h];
            }
        }
        string ausgabe(sol.begin(),sol.end());
        cout << ausgabe;
        vector<char> R(K);
        for (int j = 0; j < K; j++) {
            cin >> R[j];
            if (R[j] != '_'){
                sol[j] = R[j];
                rght[j] = true;
            }
        }
    }
        
}
    

/*
 * Reads a single string from standard input.
 */
/*string read_string() {
    string s; cin >> s;
    return s;
}

/*
 * Prints a guess to standard output and flushes the output stream buffer.
 *//*
string print_guess(string guess) {
    cout << guess << endl;
}
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
