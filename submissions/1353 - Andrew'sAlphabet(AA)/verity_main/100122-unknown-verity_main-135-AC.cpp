#include <bits/stdc++.h>
using namespace std;

int main(){
    int t; cin >> t;
    while (t--){
        int n, k; cin >> n >> k;
        vector<string> word(k);
        for (int i = 0; i < k; i++){
            cin >> word[i];
        }

        string guess = "";
        for (int i = 0; i < n; i++){
            guess+="_";
        }
        int i = 0;
        while (guess!="CORRECT" && i < k){
            for (auto&c:guess){
                if (c=='_'){
                    cout << word[i];
                } else{
                    cout << c;
                }
            }
            cout << endl;
            cin >> guess;
            i++;
        }
    }

    return 0;
}