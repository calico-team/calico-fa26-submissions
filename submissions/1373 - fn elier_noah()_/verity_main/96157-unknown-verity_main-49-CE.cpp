#include <iostream>
#include <vector>
using namespace std;

void print_guess(string guess);
string pair_to_string(vector<char>& characters);
void string_to_pair(string s, vector<char>& old, vector<char>& chars);
string read_string();

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

    // initial guess
    vector<char> characters {};
    characters.reserve(N);
    for (int i = 0; i < N; i++) {
        characters.emplace_back(A[0]);
    }
    print_guess(pair_to_string(characters));

    while (true) {
        string output = read_string();
        if (output == "CORRECT") {
            return;
        }

        string_to_pair(output, characters, A);
        print_guess(pair_to_string(characters));
    }
}

string pair_to_string(vector<char>& characters) {
    string s;
    for (auto& c : characters) {
        s += c;
    }
    return s;
}

void string_to_pair(string s, vector<char>& old, vector<char>& chars) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '_') {
            old[i] = *(std::find(chars.begin(), chars.end(), old[i])+1);
        }
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
