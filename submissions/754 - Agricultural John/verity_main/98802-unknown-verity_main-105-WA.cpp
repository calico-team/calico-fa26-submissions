// Problem 3

#include <bits/stdc++.h>
using namespace std;

void program(){
    // cout << flush

    int n, k;
    cin >> n >> k;
    char a[k];
    for(int i = 0; i < k; ++i)
        cin >> a[i];

    char result[n];
    for(int i = 0; i < k; ++i){
        string output (n, a[i]);
        cout << output << endl;
        cout << flush;

        string input;
        cin >> input;
        for(int j = 0; j < n; ++j){
            if(input[j] != '_')
                result[j] = input[j];
        }
    }

    cout << string(result) << endl;
    cout << flush;
    string input;
    cin >> input;
}

int main(){
    int t;
    cin >> t;
    while(t--){
        program();
    }

    return 0;
}