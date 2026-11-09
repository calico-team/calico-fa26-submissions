#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n, m;
    cin >> n >> m;
    vector<char> stuff;
    for(int i = 0; i<m; i++){
        char c;
        cin >> c;
        stuff.push_back(c);
    }
    string res (n, '_');
    for(int i = 0; i<m; i++){
        string guess (n, stuff[i]);
        string feedback;
        cout << guess;
        cin >> feedback;
        if(feedback.compare("CORRECT") == 0) return;
        for(int j = 0; j<n; j++){
            char c = feedback[j];
            if(c != '_'){
                res[j] = c;
            }
        }
    }
    cout << res;
    return;
}

int main()
{
    int t;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}