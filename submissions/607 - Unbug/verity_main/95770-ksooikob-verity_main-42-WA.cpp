#include <bits/stdc++.h>
using namespace std;
typedef long long li;
#define fastio ios_base::sync_with_stdio(false);cin.tie(0)
void setIO(string s) {freopen((s + ".in").c_str(), "r", stdin);freopen((s + ".out").c_str(), "w", stdout);}
li mod(li a,li b){li c=a%b;return c<0?c+b:c;}

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
    vector<char> ans(N);
    for (int k = 0; k < K; k++) {
        for (int n = 0; n < N; n++) {
            cout << A[k];
        }
        cout << endl;
        string s; cin >> s;
        for (int n = 0; n < N; n++) {
            if (s[n] == A[k]) {
                ans[n] = s[n];
            }
        }
    }
    for (int n = 0; n < N; n++) {cout << ans[n];}
    cout << endl;
    string s; cin >> s;
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