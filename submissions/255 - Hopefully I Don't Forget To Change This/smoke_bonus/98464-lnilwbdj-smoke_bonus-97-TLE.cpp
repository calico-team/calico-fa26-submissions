#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin >> t;
    while(t--){
        int n,r;
        cin >> n >> r;
        int s = 2,t = 0;
        string out = "YES";
        for(int i=0;i<n;i++){
            int a;
            cin >> a;
            while(s<2 && t<=a){
                s++;
                t+=r;
            }
            if(s==0){
                out="NO";
                continue;
            }
            else{
                if(s == 2) t=a+r;
                s--;
            }
        }
        cout << out << endl;
    }
}
