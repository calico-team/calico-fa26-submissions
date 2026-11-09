#include <iostream>
#include <vector>
#include <string>

using namespace std;

string read_string();
void print_guess(string guess);

void solve(int N, int K, vector<char> A) {
    string known = "";
    for (int j = 0; j < N; j++) {
        known += " ";
    }
    
    for (int i = 0; i < K; i++) {
        string guess = "";
        for (int j = 0; j < N; j++) {
            if (known[j] != ' ') {
                guess += known[j];
            } else {
                guess += A[i];
            }
        }

        print_guess(guess);
        string res = read_string();

        if (res == "CORRECT") {
            return;
        }

        for (int j = 0; j < N; j++) {
            if (res[j] == guess[j]) {
                known[j] = guess[j];
            }
        }
    }
}

string read_string() {
    string s;
    cin >> s;
    return s;
}

void print_guess(string guess) {
    cout << guess << endl; 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    if (cin >> T) {
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
    return 0;
}
