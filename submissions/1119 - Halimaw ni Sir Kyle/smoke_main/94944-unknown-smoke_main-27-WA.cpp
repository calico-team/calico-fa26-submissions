#include <iostream>
#include <vector>
using namespace std;

/**
 * Print one line for each token in S to draw the cookie.
 *
 * S: cookie name
 */
void solve(int N, int R, vector<int> A) {
    
    bool possible = true;
    int Charges = 1;
    int Time = A[0];
    for(int i = 1; i < N; i++){
        if(A[i] - Time >= R){
            int Chargeback = (A[i] - Time)/R;
            Charges = max(2, Chargeback);
        } else{
            possible = false;
        }
        Time = A[i];
        Charges--;
    }
    
    if(possible){
        cout << "YES" << endl;
    } else{
        cout << "NO" << endl;
    }

    return;
}

int main() {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N;
        int R;
        cin >> N;
        cin >> R;
        vector<int> A;
        for(int i = 0; i < N; i++){
            int x; cin >> x;
            A.push_back(x);
        }
        solve(N, R, A);
    }
}