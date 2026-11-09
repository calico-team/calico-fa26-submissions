#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<iterator>
#include<string>
#include<sstream>
#include<queue>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<numeric>
#include<iomanip>
#include<map>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(nullptr);
    int t;cin>>t;
    for(int id=0;id<t;id++){
        int n,r;
        cin>>n>>r;
        if(n<3){
            int x;
            for(int i=0;i<n;i++){
                cin>>x;
            }
            cout<<"YES"<<'\n';
        }
        else{
            long long previous;
            pair<long long,long long>times={0,0};
            long long a;
            cin>>a;
            cin>>previous;

            bool flag=true;
            if(times.first<=a){
                times.first=max(a,times.second)+r;
            }
            else if(times.second<=a) {
                times.second=max(a,times.first)+r;
            }
            else{
                flag=false;
            }
            if(flag){
                if(times.first<=previous){
                    times.first=max(previous,times.second)+r;
                }
                else if(times.second<=previous){
                    times.second=max(previous,times.first)+r;
                }
                else{
                    cout<<"NO"<<'\n';
                    flag=false;
                }
            }

            for(int i=2;i<n;i++){
                long long x;cin>>x;
                if(flag){
                    if(times.first<=x){
                        times.first=max(x,times.second)+r;
                    }
                    else if(times.second<=x){
                        times.second=max(x,times.first)+r;
                    }
                    else{
                        cout<<"NO"<<'\n';
                        flag=false;
                    }
                }
                previous=x;
            }
            if(flag){
                cout<<"YES"<<'\n';
            }
        }
    }
}