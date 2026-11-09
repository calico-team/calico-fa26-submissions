#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int t;
    cin >> t;
    
    for (int i = 0; i < t; i++) {
        int n, k;
        string s;
        cin >> n >> k;
        
        for (int j = 0; j < k; j++) {
            char inp;
            cin >> inp;
            s.insert(s.begin(), inp);
        }
        bool cont = true;
        
        vector<int> ind(n, 0);
        
        while (cont) {
            string out;
            for (int a = 0; a < n; a++) {
                out += s[ind[a]];
            }
            
            string res;
            cout << out << endl;
            
            cin >> res;
            
            if (res == "CORRECT") {
                cont = false;
                break;
            }
            
            for (int b = 0; b < n; b++) {
                if (res[b] == '_') {
                    ind[b]++;
                }
            }
        }
    }
}