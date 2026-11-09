//written by sarah
#include <bits/stdc++.h>
using namespace std;

string solve(int n, int k, vector<char>& a, int guess) {
    string ans;
    for (int i=0; i<k; i++) {
        if (a[i]!='_') {
            ans+=a[i];
        }
        else {
            ans+=a[guess];
        }
    }
    return ans;
}

string read_string() {
    string s; cin >> s;
    return s;
}

string print_guess(string guess) {
    cout << guess << endl;
}

int main() {
    int T;
    cin >> T;

    for (int i=0; i<T; i++) {
        int N, K;
        cin >> N >> K;

        vector<char> A(K);
        for (int j=0; j<K; j++) {
            cin >> A[j];
        }

        int guess=0;
        string ans;
        string str;
        while (str!="CORRECT") {
            ans=solve(N, K, A, guess);
            print_guess(ans);
            guess++;
            str=read_string();
        }
    }

    return 0;
}
