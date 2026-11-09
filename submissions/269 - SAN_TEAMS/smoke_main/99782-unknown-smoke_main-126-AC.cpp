#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
	int t;
    cin >> t;
    while(t--){
        int n, r;
        cin >> n >> r;
        vector<int> a(n+1);
        
        for (int i = 1; i <= n; i++){
            cin >> a[i];
        }

        bool b = true;
        int bombas = 2;
        queue<int> ts;
        int j = 1;
        int last = 0;
        for (int i = 0; i <= a[n]; i++){
            if (bombas != 2) {
                last++;
                if (last == r){
                    last = 0;
                    bombas += 1;
                }
            }

            if (i == a[j]){
                j++;
                if (bombas<=0){
                    b = false;
                    cout << "NO\n";
                    break;
                }
                bombas--;
            }
        }
        
        if (b) cout << "YES\n";
    }
}
