#include <bits/stdc++.h>
using namespace std;

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
    // YOUR CODE HERE
    string ans = "";
    for(int i = 0; i < N; i++){
		ans += '_';
	}
	bool ac = 0;
    for (int i = 0; i < K; i++)
	{
		string guess = "";
		for (int j = 0; j < N; j++)
		{
			guess += A[i];
		}
		print_guess(guess);
		string res = read_string();
		if(res == "CORRECT"){
			ac = 1;
			break;
		}
		for(int j = 0; j < N; j++){
			if(res[j] != '_'){
				ans[j] = res[j];
			}
		}
	}
	if(!ac){
		print_guess(ans);
		string res = read_string();
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
