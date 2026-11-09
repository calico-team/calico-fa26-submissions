#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>> T;
    while (T--){
        int N;
        long long R;
        cin >>N>> R;
        vector<long long> A(N);
        for (int i= 0; i< N; i++) {
            cin >>A[i];
        }
        int charges =2;
        queue<long long> recharge;
        bool possible =true;
        for(int i= 0; i < N; i++) {
            long long t = A[i];
            while (!recharge.empty() &&recharge.front() <= t) {
                recharge.pop();
                charges++;
            }
            if (charges ==0){
                possible = false;
                break;
            }
            charges--;
            long long finishTime;
            if (recharge.empty()) {
                finishTime= t +R;
            } else {
                finishTime= recharge.back() + R;
            }
            recharge.push(finishTime);
        }
        cout <<(possible ? "YES" : "NO") <<'\n';
    }
    return 0;
}