#include <bits/stdc++.h>
using namespace std;

void solve(int N, int K, vector<char>& A) {
    string Answer(N, '_');
    for(int i = 0; i < K; i++){
        string guess(N, A[i]);
        cout << guess << endl;
        string s; cin >> s;
        if(s == "CORRECT"){
            return;
        }
        for(int j = 0; j < N; j++){
            if(s[j] != '_'){
                Answer[j] = A[i];
            }
        }
    }
    cout << Answer << endl;
    string Final; cin >> Final;
    return;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(NULL); 

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
