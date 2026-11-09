#include <iostream>
#include <vector>
using namespace std;


int main(){
    int t;
    cin >> t;
    for(int i = 0;i < t;i++){
        int n,r;
        cin >> n >> r; // n = smoke req, r == seconds needed for smoke to recharge
        vector<int> a; // with the size of n
        for (int i = 0; i < n; i++) {
            int dum;
            cin >> dum;
            a.push_back(dum);
        }
        int smoke_1_using_time = 0;
        int smoke_2_using_time = 0;
        for (int i = 0; i < n; i++) {
            if (smoke_1_using_time < a[i]) {
                smoke_1_using_time=a[i]+r;
                if (i == n-1) {
                    cout << "YES" << endl;
                }
            } else if (smoke_2_using_time < a[i]) {
                smoke_2_using_time=smoke_1_using_time+r;
            } else {
                cout << "NO" << endl;
                break;
            }
        }

    }
    return 0;
}