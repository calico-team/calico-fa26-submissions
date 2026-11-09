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

    bool done = false;

    for(int i = 0; i < k; ++i){
        string output (n, a[i]);
        cout << output << endl;
        cout << flush;

        string input;
        cin >> input;
        if(!input.compare("CORRECT")){
            done = true;
            break;
        }
        for(int j = 0; j < n; ++j){
            if(input[j] != '_')
                result[j] = input[j];
        }
    }

    if(!done){
        string outputString;
        for(char c: result)
            outputString += c;
        cout << outputString << endl;
        string input;
        cin >> input;
    }
}

int main(){
    int t;
    cin >> t;
    while(t--){
        program();
    }

    return 0;
}