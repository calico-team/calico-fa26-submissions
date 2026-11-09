#include <bits/stdc++.h>
using namespace std;
using ll = long long;
string query(string guess){
    cout << guess << endl;
    string res; cin >> res;
    return res;
}
void solve(){
    ll N,K;cin>>N>>K;
    vector<char> chars(K);
    for (char& c : chars){
        cin >> c;
    }
    vector<string> guesses;
    for (char c : chars){
        string guess;
        for (ll i=0;i<N;i++){
            guess+=c;
        }
        string queried = query(guess);
        if (queried=="CORRECT"){
            return;
        }
        guesses.push_back(queried);
    }
    string ans;
    for (ll i=0;i<N;i++){
        char c;
        for (ll j=0;j<K;j++){
            if (guesses[j][i]!='_'){
                c=guesses[j][i];
            }
        }
        ans += c;
    }
    string queried = query(ans);
    if (queried=="CORRECT"){
        return;
    }
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) solve();
}