// Source: https://usaco.guide/general/io
#include <bits/stdc++.h>
#include <vector>
using namespace std;
int main() {
	int t;
    cin>>t;
    while(t--){
        int n, k;
        cin>>n>>k;
        vector<char> alphabet(k);
        for(int i=0;i<k;i++){
            cin>>alphabet[i];
        }
        string guess(n, alphabet[0]);
        for(int i=0; i<n;i++)guess[i]=alphabet[i % k];
        cout<<guess<<endl;
    }
}
