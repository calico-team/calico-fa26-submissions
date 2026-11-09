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


int solve(int N, int M, int K, vector<int> &P) {
    vector<bool> class_done(N, false);
    vector<int> available(N, false);
    vector<vector<int>> combs(N);
    for(int i = 0; i < N; i++) {
        if(P[i] != 0) {
            combs[P[i] - 1].push_back(i);
        }
    }
    int over_ct = 0;
    for(int b = 0; b < N; b++) {
        if(P[b] == 0) {
            available[b] = true;
        }
    }

    for(int sem = 0; sem < M; sem++) {
        int cl_ct = 0;
        vector<int> new_avb;
        for(int a = 0; a < N && cl_ct < K; a++) {
            if(available[a] == true && !class_done[a]) {
                class_done[a] = true;
                cl_ct++;
                for(int sub : combs[a]) {
                    new_avb.push_back(sub);
                }
            }
        }
        over_ct += cl_ct;
        for(int nvb : new_avb) {
            available[nvb] = true;
        }
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