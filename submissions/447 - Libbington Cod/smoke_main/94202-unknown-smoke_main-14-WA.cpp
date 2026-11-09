// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
    cin>>t;
    while(t--){
        int n,r;
        cin>>n>>r;
        vector<int> a(n);
        for(int i=0;i<n;i++)cin>>a[i];
        int count=0;
        for(int i=1;i<n;i++){
            if(a[i]-a[i-1]<r){
                count++;
            }
        }
        if(count>=2){
            cout<<"NO"<<endl;
        }
        else{
            cout<<"YES"<<endl;
        }
    }
}
