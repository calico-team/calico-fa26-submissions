#include <iostream>
using namespace std;

int main(){
    int T; cin >> T;
	while (T--) {
        int n;
        int r;
        cin >> n >> r;
        int charges = 2;
        int next = 0;
        bool possible = true;
        for (int i = 0; i < n; i++){
            int a;
            cin >> a;
            if (charges < 2 && next <= a){
                charges++;
                next += r;
            }
            if (charges < 2 && next <= a){
                charges++;
                next += r;
            }
            if (charges == 0) possible = false;
            else {
                if (charges == 2) next = a + r;
                charges--;
            }
        }

        if (possible){
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}