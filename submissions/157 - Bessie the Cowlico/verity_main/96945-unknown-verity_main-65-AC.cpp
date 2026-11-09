#include <iostream>
#include <vector>
using namespace std;
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
    return guess;
}

/*
 * Print a sequence of guesses until you guess the answer string.
 * You may use the read_string() and print_guess() helper functions defined below.
 *
 * N: Length of the string
 * K: Number of different -ities
 * A: List containing the different -ities
 */
void solve(int n, int k, vector<char>& a) {
    string ans,guess,res="";
    for (int i=0;i<n;++i){
        ans+='_';
    }
    for (int i=0;i<a.size();++i){
        guess.clear();
        for (int j=0;j<n;++j){
            guess+=a[i];
        }
        print_guess(guess);
        res=read_string();
        if (res=="CORRECT") return;
        for (int j=0;j<res.length();++j){
            if (res[j]!='_'){
                ans[j]=a[i];
            }
        }
    }
    print_guess(ans);
    read_string();
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
        // cout<<"complete"<<endl;
    }

    return 0;
}
