#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >>t;
    while(t--){
        int n, k;
        cin>>n>>k;
        vector<char> letters(k);
        for (char &j : letters) cin >> j;
        vector<char> word(n, '_');
        for (char j : letters){
            string s = "";
            for (int i = 0; i < n; i++) s+=j;
            cout << s << '\n';
            string res;
            cin >> res;
            if (res=="CORRECT") break;
            for (int i = 0; i < res.size(); i++){
                if (word[i]=='_'&&res[i]!='_') word[i] = res[i];
            }
        }
        string out = "";
        for (int i = 0; i<word.size(); i++) out+=word[i];
        cout << out << '\n';
        string s; cin >> s;
    }
}
