#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >>T;
    while (T--){
        int N, K;
        cin >>N >> K;
        vector<char>letters;
        bool seen[26]= {};
        for(int i =0; i < K; i++){
            char c;
            cin >>c;
            if (!seen[c -'A']) {
                seen[c - 'A'] =true;
                letters.push_back(c);
            }
        }
        string ans(N,'?');
        for (char c : letters) {
            string guess(N, c);
            for(int i= 0; i < N; i++){
                if (ans[i] != '?'){
                    guess[i] =ans[i];
                }
            }
            cout <<guess<< '\n' << flush;
            string response;
            if (!(cin >>response)) {
                return 0;
            }
            if (response== "CORRECT") {
                break;
            }
            for(int i = 0; i < N;i++) {
                if (response[i]!= '_') {
                    ans[i] = response[i];
                }
            }
        }
    }
    return 0;
}