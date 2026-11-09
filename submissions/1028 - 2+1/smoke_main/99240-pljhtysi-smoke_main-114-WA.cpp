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
        for (int i = 0; i < n; i++) cin >> a[i];

        bool can = 1,used =0; int temp = 0;
        for (int i = 0; i < n; i++) {
            if (temp <= a[i]) {
                temp = a[i]+r;
            }
            else if (temp > a[i] && !used) {
                used = 1;
            }
            else {
                can = 0; break;
            }
        }
        (can) ? cout << "YES" : cout << "NO";
        cout << endl;
    }
    
}
