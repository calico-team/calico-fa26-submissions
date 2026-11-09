#include <bits/stdc++.h>
using namespace std;
using ll = long long;
string read_string(){
    string s; cin >> s;
    return s;
}
void print_guess(vector<char>& guess){
    for (char i : guess){
        cout << i;
    }
    cout << '\n';
    cout.flush();
}
void solve(ll N, ll K, vector<char>& A){
    vector<char> B(N, '_');
    vector<char> envio;
    for (char c : A){
        for (int i = 0; i < N; i++){
            envio.push_back(c);
        }
        print_guess(envio);
        string s = read_string();
        if (s == "CORRECT"){
            return;
        }
        for (int i = 0; i < N; i++){
            if (s[i] != '_' && B[i] == '_'){
                B[i] = s[i];
            }
        }
        
        envio.clear();
    }
    print_guess(B);
    string s = read_string();
    if (s == "CORRECT"){
            return;
    }
}

int main() {
    ll T; cin >> T;
    for (int i = 0; i < T; i++) {
        ll N, K;
        cin >> N >> K;
        vector<char> A(K);
        for (int j = 0; j < K; j++) {
            cin >> A[j];
        }
        solve(N, K, A);
    }
    return 0;
}