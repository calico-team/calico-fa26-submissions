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
int solve(int N, int M, int K, vector<int> &P){
    vector<int> taken{};
    taken.reserve(N);

    for (int i = 0; i < M; ++i) {
        int classes = 0;
        vector<int> semester_classes{};
        semester_classes.reserve(K);

        for (int j = 0; j < N; ++j) {
            int cls = j + 1;
            int req = P[j];

            if (classes == K) break;

            if (find(taken.begin(), taken.end(), cls) == taken.end() && (req == 0 || find(taken.begin(), taken.end(), req) != taken.end())) {
                semester_classes.push_back(j);
                classes++;
            }
        }

        for (int k : semester_classes) {
            taken.push_back(k + 1);
        }
    }

    return taken.size();
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--){
        int N, M, K; cin >> N >> M >> K;
        vector<int> P(N);
        for (int i = 0; i < N; i++) cin >> P[i];
        cout << solve(N, M, K, P) << endl;
    }
}