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
        int rec = 0;
        int ti = 1;
        
        while (ti <= maxT) {
            if (smoke < 2) {
                rec++;
                if (rec == r) {
                    smoke++;
                    rec = 0;
                }
            } else {
                rec = 0;
            }
            
            if (ti == arr[0]) {
                if (smoke == 0) {
                    sol = false;
                    break;
                } else {
                    smoke--;
                    arr.erase(arr.begin());
                }
            }
            
            ti++;
        }
        
        if (sol) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    
    return 0;
    
}