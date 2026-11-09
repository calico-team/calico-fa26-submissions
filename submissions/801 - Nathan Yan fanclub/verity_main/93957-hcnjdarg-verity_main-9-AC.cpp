#include <bits/stdc++.h>
using namespace std;
using ll =long long int;
string answer(string s){
    cout << s << "\n";
    cout.flush();
    string a; cin >> a;
    return a;
}
void solve(){
    int n;
    cin >> n;
    ll k;
    cin >> k;
    vector <char> l1(k);
    for (int i = 0; i < k; i++) cin >> l1[i];
    vector <bool> correct(n, false);
    vector <ll> v(n, 0);
    while (true){
        string query = "";
        for (int i = 0; i < n; i++){
            query += l1[v[i]];
        }
        string myanswer = answer(query);
        if (myanswer == "CORRECT") return;
        for (int i = 0; i < n; i++){
            if (myanswer[i] == '_'){
                v[i]++;
            }
        }
    }  
}
int main(){
    int t;
    cin >> t;
    while (t--){
        solve();
    }
    return 0;
}