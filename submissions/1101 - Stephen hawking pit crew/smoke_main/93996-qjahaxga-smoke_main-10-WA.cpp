#include <bits/stdc++.h>
#define f first
#define s second
using ll=long long;
using ull=unsigned long long;
using namespace std;
int main() {
    int t; cin >> t;
    while(t--) {
        int n, r; cin >> n >> r;
        vector<int> v(n);
        for(int i=0; i<n; i++) cin >> v[i];
        int nxt=v[0]+r;
        bool b=true;
        for(int i=2; i<n; i++) {
            if(v[i]<nxt) {
                b=false;
                break;
            }
            nxt=v[i]+r;
        }
        if(b) cout << "YES\n";
        else cout << "NO\n";
    }
}