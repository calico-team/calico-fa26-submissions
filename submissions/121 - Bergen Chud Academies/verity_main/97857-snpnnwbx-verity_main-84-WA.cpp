#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n, k;
    cin >> n >> k;

    char c[k];

    for (int i = 0; i < k; i ++){
        cin >> c[i];
    }
    char out[n];

    for (char i : c){
        for (int j = 0; j < n; j ++){
            cout << i;
        }
        cout << "\n";
        fflush(stdout);
        for (int j = 0; j < n; j ++){
            char c2;
            cin >> c2;
            if (c2 != '_'){
                out[j] = c2;
            }
        }
    }
    for (char i : out){
        cout << i;
    }
    cout << "\n";
    fflush(stdout);
    string s;
    cin >> s;
    //fflush(stdout);
}

int main(){
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}