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
        a.push_back(0);
        for (int i = 1; i <= n; i++){
            cin >> a[i];
        }

        bool b = true;
        int bombas = 2;

        for (int i = 1; i <= n; i++){
            if (a[i]-a[i-1] >= 2*r) {
                bombas += 2;
                bombas = min(bombas, 2);
                
            } else if (a[i]-a[i-1] >= r){
                bombas += 1;
                bombas = min(bombas, 2);
            }

            if (bombas == 0){
                b = false;
                cout << "NO\n";
                break;
            }
            
            bombas--;
            
        }
        if (b) cout << "YES\n";
        
    }
}
