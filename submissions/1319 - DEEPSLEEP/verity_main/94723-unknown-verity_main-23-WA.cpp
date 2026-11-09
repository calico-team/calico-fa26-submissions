#include<bits/stdc++.h>
using namespace std;
const int N = 105;
char c[N];
int T, n, k;
char ans[N];
bool vis[N];
int main(){
    cin >> T;
    while(T--){
        cin >> n >> k;
        for(int i = 1; i <= k; ++i){
            cin >> c[i];
        }
        for(int i = 1; i <= n; ++i){
            vis[i] = false;
        }
        for(int i = 1;; ++i){
            for(int j = 1; j <= n; ++j){
                if(!vis[j]) cout << c[i] << " ";
                else cout << ans[j] << " ";
            }
            cout << endl; cout.flush();
            string s;
            cin >> s;
            if(s == "CORRECT") break;
            for(int j = 1; j <= n; ++j){
                char c = s[j - 1];
                if(c != '_'){
                    // cout << j << " " << c << endl;
                    vis[j] = 1;
                    ans[j] = c;
                }else vis[j] = 0;
            }
        }
    }
    return 0;
}/*
T3 Verity
一百次猜测?
n <= 100 k <= 26
*/