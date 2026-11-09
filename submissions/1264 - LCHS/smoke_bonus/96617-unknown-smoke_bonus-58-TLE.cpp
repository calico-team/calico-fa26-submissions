#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        int n, r;
        cin >> n >> r;
        
        vector<int> arr(n);
        
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        
        int maxT = arr.back();
        bool sol = true;
        int smoke = 2;
        int rec = r;
        int ti = 1;
        
        while (!arr.empty()) {
            int n = arr[0];
            int diff = n - ti;
            
            if (smoke == 0) {
                if (diff >= rec) {
                    smoke++;
                    diff -= rec;
                    rec = r;
                }
            }
            
            if (smoke == 1) {
                if (diff >= rec) {
                    smoke++;
                    diff -= rec;
                    rec = r;
                }
            }
            
            rec -= diff;
            ti = n;
        
            if (smoke == 0) {
                sol = false;
                break;
            } else {
                smoke--;
                if (smoke == 1) {
                    rec = r;
                }
                arr.erase(arr.begin());
            }
        }
        
        if (sol) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    
    return 0;
    
}