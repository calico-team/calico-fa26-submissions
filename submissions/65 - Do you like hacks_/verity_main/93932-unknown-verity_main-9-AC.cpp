#include<bits/stdc++.h>
using namespace std;
#define ll long long
char a[30];
int main(){
    int T;
    cin >> T;
    while(T--){
        int n, k;
        cin >> n >> k;
        for(int i=0; i<k; ++i){
            cin >> a[i];
        }
        string s="";
        for(int i=0; i<n; ++i) s+=a[0];
        for(int i=0; i<k+1; ++i){
            cout << s << endl; 
            string A; cin >> A;
            if(A=="CORRECT") break;
            for(int j=0; j<n; ++j){
                if(A[j]=='_') s[j]=a[i+1];
            }
        }
        // cout << s << '\n';
    }
    return 0;
}