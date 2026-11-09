#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

/** 
 * Return the maximum number of classes that can be taken across M semesters.
 *    
 * N: the number of classes
 * M: the number of semesters
 * K: the maximum number of classes you can take per semester
 * P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
 */

void pt(priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> tp){
    cout << "open: ";
    while(!tp.empty()){
        cout << tp.top().second;
        tp.pop();
    }
    cout << endl;
}

void cadj(vector<vector<int>> adj){
    int ct = 0;
    for(auto i : adj){
        cout << "adj to " << ct << ": ";
        for(auto j : i){
            cout << j << " ";
        }
        ct++;
        cout << endl;
    }
}

void solve(int N, int M, int K, vector<int> &P){
    // cout << "N:  "<< N << " M: " << M << " K: " << K << endl;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> open;
    vector<vector<int>> revP(N);

    set<int> no;
    for(int i = 0; i < N; i++){
        if(P[i] != -1){
            revP[P[i]].push_back(i);
        } else {
            no.insert(i);
        }
    }

    for(int i : no) open.push({revP[i].size(), i});
    // cout << "revP: \n";
    // cadj(revP);

    int taken = 0;

    // pt(open);

    for(int i = 0; i < M; i++){
        vector<pair<int, int>> f;
        vector<pair<int, int>> topush;
        for(int j = 0; j < K; j++){
            if(open.empty()) break;
            f.push_back(open.top());
            open.pop();
        }
        for(int j = 0; j < f.size(); j++){
            taken++;
            for(int l : revP[f[j].second]){
                topush.push_back({revP[l].size(), l});
            }
        }
        for(auto j : topush) open.push(j);
        // cout << " after i = " << i << " open becomes ";
        // pt(open);
    }

    cout << taken << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--){
        int N, M, K; cin >> N >> M >> K;
        vector<int> P(N);
        for (int i = 0; i < N; i++){
            cin >> P[i];
            P[i]--;
        }
        solve(N, M, K, P);
    }
}