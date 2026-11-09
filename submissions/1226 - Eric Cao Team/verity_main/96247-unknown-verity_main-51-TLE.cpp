#include <iostream>
#include <vector>
using namespace std;

string read_string() {
    string s; cin >> s;
    return s;
}

string print_guess(string guess) {
    cout << guess << endl;
    return guess;
}

void solve(int N, int K, vector<char>& A) {
    string guess(A.begin(), A.end());
    for (int i = 0; i < K; i++){
        print_guess(guess);
        string response = read_string();
        if (response == "CORRECT") return;
        guess = response;
        if (i+1 < K){
            for (int j = 0; j < N; j++){
                if (guess[j] == '_') guess[j] = A[i+1];
            }
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

        solve(N, K, A);
    }

    return 0;
}
