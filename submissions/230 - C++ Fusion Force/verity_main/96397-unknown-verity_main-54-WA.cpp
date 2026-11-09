//written by sarah
#include <bits/stdc++.h>
using namespace std;

string solve(int n, int k, string a, string str, int guess) {
    string ans;
    for (int i=0; i<k; i++) {
        if (str[i]!='_') {
            ans+=str[i];
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

void print_guess(string guess) {
    cout << guess << endl;
}

int main() {
    int T;
    cin >> T;

    for (int i=0; i<T; i++) {
        int N, K;
        cin >> N >> K;

        string a;
        char c;
        for (int j=0; j<K; j++) {
            cin >> c;
            a+=c;
        }

        int guess=0;
        string ans, str=a;
        while (str!="CORRECT") {
            ans=solve(N, K, a, str, guess);
            print_guess(ans);
            // a=ans;
            guess++;
            if (guess==K) guess=0;
            str=read_string();
        }
    }
    return 0;
}
