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

void solve2 (int N, int K, vector<char>& A){
    
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N, K;
        int tester = 0;
        cin >> N >> K;
        vector<char> A(K);
        for (int j = 0; j < K; j++) {
            cin >> A[j];
        }
        vector<char>sol(N);
        vector<bool>rght(N,false);
        int test = 0;
        for (int x = 0; x < 4; x++){
            if (tester != 1) {
            test = 1;
            for (int i = 0; i < N; i ++){
                if (!rght[i]) {
                    test = 0;
                }
            }
            if (test != 1){
                test = 1;
                for (int i = 0; i < N; i ++){
                    if (!rght[i]) {
                        test = 0;
                        sol[i] = A[x];
                    }
                }
                string ausgabe(sol.begin(),sol.end());
                cout << ausgabe << endl;
                
                string Q;
                cin >> Q;
                if (Q != "CORRECT"){
                    for (int h = 0; h < Q.length(); h ++){
                        if (Q[h] != '_'){
                            sol[h] = Q[h];
                            rght[h] = true;
                        }
                    }
                } else {
                    tester = 1;
                }
            }
            }   
        }
    }
    return 0;

}