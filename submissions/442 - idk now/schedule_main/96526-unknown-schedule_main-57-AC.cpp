#include <iostream>
#include <vector>
#include<deque>
#include<queue>
#define fi first
#define se second 
#define ll long long
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
    vector<vector<int>>child(N+1);
    for(int i = 1;i<=N;i++){
        child[P[i-1]].push_back(i);
    }
    deque<pair<int,int>>dq;//layer-node
    vector<vector<int>>layer(M+1);
    dq.push_back({0,0});
    while(dq.size()){
        auto[d,node] = dq.back();
        dq.pop_back();
        if(d>M)continue;
        layer[d].push_back(node);
        for(int des:child[node]){
            dq.push_front({d+1,des});
        }
    }
    int ans = 0,curr = 0;
    for(int i = M;i>0;i--){
        curr += K;
        int x = layer[i].size();
        if(x<=curr){
            curr -= x;
            ans += x;
        }else{
            ans += curr;
            curr = 0;
        }
    }
    cout<<ans<<'\n';
    return -1;
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