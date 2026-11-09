#include <bits/stdc++.h>
using namespace std;

using LL = long long;
/**
 * Print one line for each token in S to draw the cookie.
 *
 * S: cookie name
 */
void solve(int N, int R, vector<int> A) {
    
    bool possible = true;
    int Charges = 2;
    
    queue<LL> recharge;

    for(int i=0; i<N; i++){
        
        while(!recharge.empty() && recharge.front() <= A[i]){
            recharge.pop();
            Charges++;
        }
        
        if(Charges == 0){
            possible = false;
            break;
        }

        Charges--;

        LL recharged;
        if(recharge.empty()){
            recharged = (LL)A[i] + R;
        }
        else{
            recharged = recharge.back() + R;
        }

        recharge.push(recharged);
    }

    if(possible){
        cout << "YES" << endl;
    }
    else{
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
