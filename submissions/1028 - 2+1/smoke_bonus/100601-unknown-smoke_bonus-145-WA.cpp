#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int t; cin >> t;
    while (t--) {
        int n, r; cin >> n >> r;
        vector<int> a(n);
        bool can = 1; 
        int temp1 = 0, temp2 = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (temp1 > a[i]) {
                if (temp2 > a[i]) {
                    can = 0; break;
                }
                else {
                    temp2 = temp1 + r;
                }
            }
            else {
                temp1 = a[i] + r;
            }
        }
        (can) ? cout << "YES" : cout << "NO";
        cout << endl;
    }
    
}
