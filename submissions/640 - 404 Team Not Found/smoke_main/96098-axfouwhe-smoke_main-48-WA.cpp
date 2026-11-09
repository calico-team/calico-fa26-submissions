#include <iostream>
using namespace std;

int main(){
    int t;
    cin >> t;
    for(int i = 0;i < t;i++){
        int n, r;
        int a[1000] = {0};
        bool flag = 1;
        cin >> n >> r;
        for(int j = 0;j < n;j++){
            cin >> a[j];
        }
        int charge = 2;
        for(int j = 1;j <= n;j++){
            if((a[j] - a[j - 1]) < r){
                if(charge == 0){
                    flag = 0;
                    break;
                }
                else{
                    charge--;
                }
            }
        }
        if(flag == 1){
            cout << "Yes" << endl;
        }
        else{
            cout << "No" << endl;
        }
    }
    return 0;
}