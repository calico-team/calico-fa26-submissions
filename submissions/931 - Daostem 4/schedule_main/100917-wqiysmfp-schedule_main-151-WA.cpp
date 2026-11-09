#include <bits/stdc++.h>
#include <vector>
using namespace std;
 vector<int>trans(vector<int>P){
         for(long unsigned int i = 0; i<P.size(); i++){
                 if(P[i] == -2) P[i] = -1;
         }
         return P;
 }
int solve(int N, int M, int K, vector<int> &P){
        int acc = K;

        int ans = 0;
        for(int i = 0; i<M; i++){
                for(long unsigned int j = 0; j<P.size(); j++){
                        if(P[j] == 0 || P[P[j]-1] == -1){
                                ans++;
                                acc--;
                                P[j] = -2;
                                if(acc==0) break;
                                
                        }
                       
                }
               
                acc = K;
                P = trans(P);
                
        }
        return ans;
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