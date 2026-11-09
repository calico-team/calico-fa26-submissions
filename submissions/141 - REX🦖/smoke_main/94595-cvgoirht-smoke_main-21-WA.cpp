#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 7;

int t, n, m;
int a[N], f[N];

void solve(){

    cin >> n >> m;
    for(int i = 1; i <= n; i ++)
        cin >> a[i], f[a[i]] = 1;
    int tml = 0, tmr = 0, OK = 0;
    for(int i = 1; i <= a[n]; i ++){
        if(f[i]){
            if(tml){
                if(!tmr) tmr = m;
                else OK = 1;
            }
            else tml = m;
        }
        if(!tml && tmr) tmr --;
        else if(tml) tml --;
        f[i] = 0;
    }
    if(OK) cout << "NO\n";
    else cout << "YES\n";

}

int main(){

    cin >> t;
    while(t --) solve();

    return 0;
}
