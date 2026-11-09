#include <iostream>
#include <vector>
using namespace std;

/** 
 * Return the maximum number of classes that can be taken across M semesters.
 *    
 * N: the number of classes
 * M: the number of semesters
 * K: the maximum number of classes you can take per semester
 * P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
 */

int G(int x, vector<vector<int>> &k, vector<int> &h) {

    h[x] = 1;

    for (int y : k[x]) {

        h[x] = max(h[x], 1 + G(y, k, h));

    }

    return h[x];

}

int solve(int N, int M, int K, vector<int> &P){
    // YOUR CODE HERE
    
    vector<vector<int>> k (N + 1);

    for (int i = 0; i < N; i++) {

        k[P[i]].push_back(i + 1);

    }

    vector<int> h(N + 1, 0);
    G(0, k, h);
    vector<vector<int>> b(1005);

    for (int c : k[0]) {

        b[h[c]].push_back(c);

    }

    int t = 0;

    for (int s = 0; s < M; s++) {

        vector<int> T;

        for (int x = 1000; x >= 1 && (int) T.size() < K; x--) {

            while (!b[x].empty() && (int)T.size() < K) {

                T.push_back(b[x].back());
                b[x].pop_back();

            }

        }

        if (T.empty()) {

            break;

        }

        t += T.size();

        for (int r : T) {

            for (int p : k[r]) {

                b[h[p]].push_back(p);

            }

        }

    }

    return t;

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--){
        int N, M, K; cin >> N >> M >> K;
        vector<int> P(N);
        for (int i = 0; i < N; i++) cin >> P[i];
        cout << solve(N, M, K, P);
    }
}