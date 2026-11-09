#include <bits/stdc++.h>
using namespace std;
string query(string guess) {
    cout << guess << endl;
    string input; cin >> input;
    return input;
}
void sol() {
    int n,k; cin>>n>>k;
    vector<char> a(k); for(int i=0; i<k; i++) cin>>a[i];
    string capaz = "";
    for(int i=0; i<n; i++) capaz+=a[0];
    bool go = true; int j = 1;
    while(go) {
        string ans = query(capaz);
        if( ans == "CORRECT") { 
            go = false;
            return;
        }
        for(int i=0; i<n; i++) {
            if(capaz[i]==ans[i]) continue;
            else capaz[i] = a[j];
        }
        j++;
    }
}
int main() {
    int t; cin>>t;
    while(t--) sol();
}