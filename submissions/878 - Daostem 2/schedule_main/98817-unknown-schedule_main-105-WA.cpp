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
    vector<vector<int>>unlock(N+1);
    vector<int> preqCt(N+1,0);
    for(int i=0; i<N; i++){
        int classid=i+1;
        int preq=P[i];
        if(preq!=0){
            unlock[preq].push_back(classid);
            preqCt[classid]++;
        }
    }
    vector<int>Take;
    for(int i=1; i<=N; i++){
        if(preqCt[i]==0) Take.push_back(i);
    }
    int tClass=0;
    for(int nsem=0; nsem < M; nsem++){
        if(Take.empty()) break;
        int numTake=min(K, (int)Take.size());
        vector<int>take;
        for(int j=0;j<numTake; j++){
        take.push_back(Take[j]);
        tClass++;
        }
        Take.erase(Take.begin(), Take.begin() + numTake);
    for(auto n:take){
        for(auto ea:unlock[n]){
            preqCt[ea]--;
            if(preqCt[ea]==0) Take.push_back(ea);
        }
    }
    }
    
    
    return tClass;
    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--){
        int N, M, K; cin >> N >> M >> K;
        vector<int> P(N);
        for (int i = 0; i < N; i++) cin >> P[i];
        cout<<solve(N, M, K, P)<<endl;
    }
}