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

        bool can = 1, one = 1, two = 1;
        int temp1 = 0, temp2 = 0;
        for (int i = 0; i < n; i++) {
            if (temp1 <= a[i] && !one) {
                one = 1; temp2 = a[i] + r;
            }
            else if (temp2 <= a[i]&& one && !two) two = 1;
            if (one) {
                temp1 = a[i] + r; one = 0;
            }
            else if (two) {
                temp2 = a[i] + r; two = 0;
            }
            else {
                can = 0; break;
            }

        }
        (can) ? cout << "YES" : cout << "NO";
        cout << endl;
    }
    
}
