#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define all(x) x.begin(), x.end()

void fill_string(string &s, char t) {
    for (char& c : s) {
        if (c == '_') {
            c = t; 
        }
    }
}

void solve() {
    int N, K; cin >> N >> K; 
    vector<char> A(K);

    for (char& c : A) cin >> c; 

    string response(N, '_'), guess = response; 
    int i = 0; 
    while (response != "CORRECT") {
        fill_string(guess, A[i++]);
        cout << guess << endl; 
        cin >> response; 
        guess = response; 
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t; cin >> t; 
    while(t--)
        solve();
}