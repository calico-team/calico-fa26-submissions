#include <bits/stdc++.h>
using namespace std;

void solve(int N, int K, vector<char>& A) {
    string Answer(N, '_');
    for(int i = 0; i < K; i++){
        string guess(N, A[i]);
        cout << guess << endl;
        string s; cin >> s;
        for(int j = 0; j < N; j++){
            if(s[j] != '_'){
                Answer[j] = A[i];
            }
        }
    }
    cout << Answer << endl;
    return;
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
