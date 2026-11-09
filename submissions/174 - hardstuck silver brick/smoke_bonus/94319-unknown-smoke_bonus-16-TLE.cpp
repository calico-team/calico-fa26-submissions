#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        long long R;
        cin >> N >> R;
        
        int charges = 2;
        long long next = 0;
        bool possible = true;
        
        for (int i=0;i<N;i++) {
            long long t;
            cin >> t;
            
            if (!possible) continue;
            while (charges<2 && next<=t) {
                charges++;
                next += R;
            }
            if (charges == 0) {
                possible = false;
                continue;
            }
            if (charges == 2) {
                next = t+R;
            }
            charges--;
        }
        cout << (possible ? "YES" : "NO") << endl;
    }
}