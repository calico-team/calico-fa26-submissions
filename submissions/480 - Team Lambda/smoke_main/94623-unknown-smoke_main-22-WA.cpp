#include <bits/stdc++.h>
using namespace std;

int main() {
    int cases;
    cin>>cases;
    for(int testcase=0; testcase<cases; testcase++){
        int n, r;
        cin>>n>>r;
        vector<int> a;
        for(int i=0; i<n; i++){
            int temp;
            cin>>temp;
            a.push_back(temp);
        }
        int c=2;
        int t=0;
        bool worked=true;
        for(int i=0; i<n; i++){
            while(c<2 && a[i]>t+r){
                c++;
                t+=r;
            }
            if(c==2){
                t=a[i];
            }
            if(c==0){
                cout<<"NO"<<endl;
                worked=false;
                break;
            } else{
                c--;
            }
        }
        if(worked){
            cout<<"YES"<<endl;
        }
    }
}
