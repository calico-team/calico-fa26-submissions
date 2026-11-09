#include <bits/stdc++.h>
using namespace std;
int main() {
    int t; 
    cin>>t;
    while(t--) {
        int n, k;
        cin >>n >> k;
        vector<char> A(k);
        for (auto &c : A){
            cin >> c;
        }
        string known(n, '?');
        for (int j=0; j<k; j++) {
            string guess = known;
            for (auto &c : guess){
                if (c=='?'){
                    c = A[j];
                }
            }
            cout<<guess<<endl; 
            string resp; cin >> resp;
            if (resp=="CORRECT"){
                break;
            }
            for(int i=0; i<n; i++){
                if (resp[i] != '_'){
                    known[i] =resp[i];
                }
            }
        }
    }
}
