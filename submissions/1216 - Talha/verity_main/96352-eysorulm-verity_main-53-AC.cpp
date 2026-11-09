#include <iostream>
#include <vector>
#include <string>
using namespace std;

string read_string() {
    string s; cin >> s;
    return s;
}

void print_guess(string guess) {
    cout << guess << endl;
}

void solve(int N, int K, vector<char>& A) {
    string known(N, '?');
    for (char c : A) {
        string guess = known;
        for (int i = 0; i < N; i++) {
            if (guess[i] == '?') guess[i] = c;
        }
        print_guess(guess);
        string resp = read_string();
        if (resp == "CORRECT") return;
        for (int i = 0; i < N; i++) {
            if (resp[i] != '_') known[i] = resp[i];
        }
    }
}

int main() {
    int T;
    if (!(cin >> T)) return 0;
    for (int i = 0; i < T; i++) {
        int N, K;
        cin >> N >> K;
        vector<char> A(K);
        for (int j = 0; j < K; j++) cin >> A[j];
        solve(N, K, A);
    }
    return 0;
}