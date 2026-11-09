// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n,K;
    cin>>n>>K;
    vector<char>chars(K);
    for(int i=0;i<K;i++){
        cin>>chars[i];
    }
    string current_guess(n,chars[0]);
    string response;
    for(int k=0;k<K;++k){
        cout<<current_guess<<endl;
        cin>>response;
        if(response=="CORRECT"){
            return;
        }
        for(int i=0;i<n;i++){
            if(response[i]!='_'){
                current_guess[i]=response[i];
            }else if (current_guess[i]==chars[k]&&k+1<K){
                current_guess[i]=chars[k+1];
            }
        }
    }
}
int main(){
    int t;
    if(cin>>t){
        while(t--){
            solve();
        }
    }
    return 0;
}