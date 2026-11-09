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


    string actual; //ACTUAL JO STRING HAI


    for(int i=0;i<N;i++){
        actual+=A[0];
    }

    vector<int> agla;

    for(int i=0;i<N;i++){
        agla.push_back(1);
    }


    while(true){

        cout<< actual << endl;

        string predict;
        cin >> predict;

        if(predict=="CORRECT"){
            break;
        }

        string ans; 

        for(int i=0;i< N; i++){

            if(predict[i]!='_'){
            actual[i]=predict[i];
            }
            else{

                actual[i]=A[agla[i]%K];
                agla[i]=agla[i]+1;
            }
        }


        // cout << ans << endl;

        

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
