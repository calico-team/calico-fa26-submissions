#include <bits/stdc++.h>
using namespace std;

int main() {
    long long cases;
    cin>>cases;
    for(long long testcase=0; testcase<cases; testcase++){
        long long n, r;
        cin>>n>>r;
        vector<long long> a;
        for(long long i=0; i<n; i++){
            long long temp;
            cin>>temp;
            a.push_back(temp);
        }
        long long c=2;
        long long t=0;
        bool worked=true;
        for(long long i=0; i<n; i++){
            while(c<2 && a[i]>=t+r){
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
