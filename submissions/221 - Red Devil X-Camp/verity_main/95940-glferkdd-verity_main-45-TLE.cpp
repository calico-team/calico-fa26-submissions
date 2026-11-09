#include <bits/stdc++.h>
#define vi vector<char> 
using namespace std;
int main() {
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        vector<char> letters(k);
        // for(int i=0;i<k;++i){
        //     char x;cin>>x;cout<<x;
        // }
        for (int i = 0; i < k; i++) cin >> letters[i];
        vector<char> correct(n);
        string guess = "";
        for (int i = 0; i < n; i++) guess+=letters[0];
        int curr = 0;
        while (true) {
            cout << guess;
            cout.flush();
            string verdict; cin >> verdict;
            if (verdict == "CORRECT") {
                break;
            }
            for (int i = 0; i < verdict.length(); i++) {
                if (verdict[i] != '_') correct[i] = letters[curr];
                else guess[i] = letters[curr+1]; 
            }
            curr++;
        }
        
    }
    return 0;
}
