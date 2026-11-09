#include <iostream>
#include <string>
#include <vector>

using namespace std;

void solve() {
    int n, k; if (!(cin >> n >> k)) return;
    
    vector<char> a(k);
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }
    
    string result(n, '_'); vector<bool> found(n, false); int remaining = n;
    
    for (int i = 0; i < k && remaining > 0; i++) {
        char ch = a[i];
        string guess = "";
        
        for (int j = 0; j < n; j++) {
            if (found[j]) {
                guess += result[j];
            } else {
                guess += ch;
            }
        }
        
        cout << guess << endl;
        
        string resp; cin >> resp;
        
        if (resp == "CORRECT") {
            return;
        }
        
        for (int j = 0; j < n; j++) {
            if (!found[j] && j < resp.length() && resp[j] != '_') {
                result[j] = resp[j]; found[j] = true;
                remaining--;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    
    return 0;
}