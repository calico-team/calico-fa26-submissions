#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
    cin >> t;
    for(int q = 0; q < t; q++){
        int n, k;
        cin >> n >> k;
        char c[k];
        string ans(n, '_');
        for(int i = 0; i < k; i++){
            cin >> c[i];
        }
        for(int i = 0; i < k; i++){
            for(int j = 0; j < n; j++){
                if(ans[j] == '_'){
                    cout << c[i];
                }else{
                    cout << ans[j];
                }
            }
            cout << '\n';

            string s;
            cin >> s;
            if(s == "CORRECT"){
                break;
            }
            for(int j = 0; j < n; j++){
                if(s[j] != '_'){
                    ans[j] = s[j];
                }
            }
        }
    }
}
