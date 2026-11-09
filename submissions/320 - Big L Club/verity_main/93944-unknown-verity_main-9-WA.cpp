#include <bits/stdc++.h>
using namespace std;
#define int long long

string answer(string s) {
    cout << s << endl;
    string res; cin >> res;
    return res;
}

string finallys(string s) 
{
    cout << s << endl;
    string correct; cin >> correct;
    return correct;
}
void solve() {
    int n,k; cin >> n >> k;
    vector<char> a(k);
    for(int i = 0; i < k; i++) cin >> a[i];

    string ans(n,a[0]);
    vector<bool> lock(n+1,false);

    for(int i = 0; i < k; i++) {
        for(int j=  0; j < n; j++) {
            if(lock[j]) continue;
            ans[j] = a[i];
        }
        string res = answer(ans);

        for(int j = 0; j < n; j++) {
            if(res[j]==ans[j]) lock[j] = true;
        }
    }
    finallys(ans);
    return;
}

signed main() {

    int t; cin >> t;
    while(t--) {
        solve();
    }
}