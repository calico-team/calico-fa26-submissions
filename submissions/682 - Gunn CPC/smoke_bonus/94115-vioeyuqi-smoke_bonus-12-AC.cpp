#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pb push_back

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        int n,m;
        cin >> n >> m;
        int c1 = 0, c2 = 0;
        bool flag = 1;
        for (int i=0;i<n;i++){
            int x;
            cin >> x;
            if (!flag){
                continue;
            }
            if (c1<=x){
                c1=x+m;
            }else if (c2<=x){
                c2=c1+m;
            }else{
                flag = 0;
                // break;
            }
        }
        if (flag){
            cout << "YES" << "\n";
        }else{
            cout << "NO" << "\n";
        }
    }
}
