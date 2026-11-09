#include <iostream>
#include <vector>
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
        vector<int> A(n);
		for (int i = 0; i < n; i++) {
			cin >> A[i];
		}

        for (int i = 0; i < n; i++){
            int a = A[i];
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
            cout << "YES" << "\n";
        } else {
            cout << "NO" << "\n";
        }
    }
}