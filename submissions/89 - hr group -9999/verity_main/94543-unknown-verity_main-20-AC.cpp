#include <bits/stdc++.h>
using namespace std;
void solve(){
    int n, k;
    cin >> n >> k;
    char arr[k];
    string s;
    for(int i = 0; i < k; i++){
        cin >> arr[i];
        //cout << arr[i] << endl;
    }
    for(int i = 0; i < n; i++){
        s.push_back(arr[0]);
    }
    cout << s << endl;
    cin >> s;
    if(s == "CORRECT"){
        return;
    }
    for(int i = 1; i < k; i++){
        for(int j = 0; j < n; j++){
            if(s[j] == '_'){
                s[j] = arr[i];
            }
        }
        cout << s << endl;
        cin >> s;
        if(s == "CORRECT"){
            return;
        }
    }
}
int main(){
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        solve();
    }
}