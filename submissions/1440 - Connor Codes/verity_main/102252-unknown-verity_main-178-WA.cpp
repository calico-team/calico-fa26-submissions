#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    // freopen("XXXXXXX.in", "r", stdin);
    // freopen("XXXXXXX.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll T;
    cin >> T;
    while(T--){
        ll N, K;
        cin >> N >> K;
        vector<char> letters(K);
        for(ll i = 0; i < K; i++){
            cin >> letters[i];
        }
        vector<char> final(N);
        for(ll i = 0; i < K; i++){
            string x(N,letters[i]);
            cout << x << endl;
            string ans;
            cerr << x << endl;
            cin >> ans;
            cerr << ans << endl;
            for(ll j = 0; j < ans.size(); j++){
                if(ans[j] != '_'){
                    final[j] = ans[j];
                }
            }
        }
        string output = "";
        for(ll i = 0; i < N; i++){
            output += final[i];
        }
        cout << output << endl;
        string correct;
        cin >> correct;
        cerr << correct << endl;
        if(correct != "CORRECT"){
            cout << output << endl;
        }
    }
}