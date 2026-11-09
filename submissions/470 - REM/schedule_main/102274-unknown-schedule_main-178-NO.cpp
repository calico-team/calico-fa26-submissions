# include <bits/stdc++.h>
using namespace std;

/** 
 * Return the maximum number of classes that can be taken across M semesters.
 *    
 * N: the number of classes
 * M: the number of semesters
 * K: the maximum number of classes you can take per semester
 * P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
 */
int solve(int N, int M, int K, vector<int> &vec){
    /*
    vector<bool> is_possible;
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (vec[i] == 0) {
            is_possible.push_back(false);
        } else {
            is_possible.push_back(true);
        }
    }
    multiset<tuple<int, vector<int>, int>> ms;
    vector<int> post_req[N];
    for (int i = 0; i < N; i++) {
        if (vec[i] != 0) {
            post_req[vec[i]-1].push_back(i);
        }
    }
    for (int i = 0; i < N; i++) {
        tuple<int,vector<int>,int> t(post_req[i].size(), post_req[i], i);
        if (is_possible[i])
            ms.insert(t);
    }

    for (int i = 0; i < M; i++) {
        vector<int> unlocked_courses;
        for (int i = 0; i < K; i++) {
            tuple<int, vector<int>, int> t = *ms.rbegin();
            vector<int> vec = get<1>(t);
            for (int i = 0; i < vec.size(); i++) {
                unlocked_courses.push_back(vec[i]);
            }
        }
    }*/
    
    int arr[N];
    for (int i = 0; i < N; i++) {
        arr[i] = -1;
    }
   vector<int> post_req[N];
    for (int i = 0; i < N; i++) {
        if (vec[i] != 0) {
            post_req[vec[i]-1].push_back(i);
        }
    }
    for (int i = 0; i < N; i++) {
        if (vec[i] == 0) {
            arr[i] = 1;
        }
    }
    
    set<int> s;
    for (int i = 0; i < N; i++) {
        if (vec[i] == 0) {
            s.insert(arr[i]);
        }
    }
    set<int> next;
    int total = 0;
    int count = 0;
    int num = 0;
    for (int i = 0; i < M; i++) {
        for (int k : s) {
            for (int j = 0; j < post_req[k].size(); j++) {
                next.insert(post_req[k][j]);
            }
        }
        count = min(K, total + (int) s.size());
        num += count;
        total -= count;
        s = next;
    }
    return num;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--){
        int N, M, K; cin >> N >> M >> K;
        vector<int> P(N);
        for (int i = 0; i < N; i++) cin >> P[i];
        solve(N, M, K, P);
    }
}