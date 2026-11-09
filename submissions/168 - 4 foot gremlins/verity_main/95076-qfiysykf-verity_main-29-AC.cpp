#include <bits/stdc++.h>
using namespace std;

void change(string &guess, int n, char newChar, string resp){
    for(int i = 0; i < n; i++){
        if(resp[i]=='_'){
            guess[i] = newChar;
        }
    }
}

void solve(){
    int n,k; cin >> n >> k;
    vector<char> options(k,0);
    for(int i = 0; i < k; i++) cin >> options[i];
    string resp = "";
    for(int i = 0; i < n; i++) resp+="_";
    string guess;
    for(int i = 0; i < n; i++) guess+=options[0];
    int ind = 1;
    while(true){
        cout << guess << endl;
        cin >> resp;
        if(resp=="CORRECT") break;
        change(guess, n, options[ind] ,resp);
        ind++;
    }
}


int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;

    while(t--) solve();

    return 0;
}
