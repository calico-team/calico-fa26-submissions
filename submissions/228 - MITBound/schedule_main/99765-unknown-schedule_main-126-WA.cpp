#include <bits/stdc++.h>
using namespace std;

/** 
 * Return the maximum number of classes that can be taken across M semesters.
 *    
 * N: the number of classes
 * M: the number of semesters
 * K: the maximum number of classes you can take per semester
 * P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
 */




int solve(int N, int M, int K, vector<int> &P){
    vector<bool> class_done(N, false);
    int over_ct = 0;
    for(int sem = 0; sem < M; sem++) {
        vector<int> available;
        for(int i = 0; i < N; i++) {
            if(class_done[i]) {
                continue;
            }
            if(P[i] == 0 || class_done[P[i] - 1]) {
                available.push_back(i);
            }
        }
        if(available.empty()) {
            break;
        }
        int take = min(K, (int)available.size());
        for(int i = 0; i < take; i++) {
            class_done[available[i]] = true;
        }
        over_ct += take;
    }
    return over_ct;
}       




int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--){
        int N, M, K; cin >> N >> M >> K;
        vector<int> P(N);
        for (int i = 0; i < N; i++) cin >> P[i];
        cout << solve(N, M, K, P) << '\n';
    }
}