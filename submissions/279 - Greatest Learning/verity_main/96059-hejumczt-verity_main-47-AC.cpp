#include <bits/stdc++.h>
using namespace std;
#define int long long


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
    // YOUR CODE HERE
    vector<char> answer(N);
    
    for (char letter: A){
		print_guess(string(N, letter));
		string response = read_string();
		if (response == "CORRECT"){
			return;
		}
		for (int i = 0; i < N; i++){
			if (response[i] != '_'){
				answer[i] = letter;
			}
		}
	}
	string string_ans = "";
	for (char i: answer){
		string_ans += i;
	}
	print_guess(string_ans);
	read_string();
	
    
    
}

/*
 * Reads a single string from standard input.
 */


int32_t main() {
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
