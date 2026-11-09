#include<bits/stdc++.h>
using namespace std;
int T,N,K;
int main(){
    cin>>T;
    while(T--){
        cin>>N>>K;
        vector<char> A(K);
        for(int i=0;i<K;i++) cin>>A[i];
        vector< set<char> > cand(N);
        for(int i=0;i<N;i++){
            for(int j=0;j<K;j++) cand[i].insert(A[j]);
        }
        while(true){
            string guess(N,' ');
            for(int i=0;i<N;i++){
                guess[i]=*cand[i].begin();
            }
            cout<<guess<<endl;
            string res;
            cin>>res;
            if(res=="CORRECT") break;
            for(int i=0;i<N;i++){
                if(res[i]!='_'){
                    cand[i].clear();
                    cand[i].insert(res[i]);
                }else{
                    cand[i].erase(guess[i]);
                }
            }
        }
    }
    return 0;
}
