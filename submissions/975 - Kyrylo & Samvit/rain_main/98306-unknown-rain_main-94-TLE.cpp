// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

struct Drone{
    long long x,y,z;
    char dir;
};
void solve(){
    int N,K;
    cin>>N>>K;
    vector<Drone>drones(N);
    for(int i=0;i<N;i++){
        cin>>drones[i].x>>drones[i].y>>drones[i].z>>drones[i].dir;
    }
    long long total_rain=0;
    for(int k=0;k<K;++k){
        for(int i=0;i<N;i++){
            bool covered=false;
            for(int j=0;j<N;j++){
                if(i!=j&&drones[i].x==drones[j].x&&drones[i].y==drones[j].y&&drones[i].z<drones[j].z){
                    covered=true;
                    break;
                }
            }
            if(!covered){
                total_rain++;
            }
        }
        for(int i=0;i<N;i++){
            if(drones[i].dir=='E'){
                drones[i].x++;
            }else if(drones[i].dir=='N'){
                drones[i].y++;
            }
        }
    }
    cout<<total_rain<<endl;
}
int main() {
	int t;
    if(cin>>t){
        while(t--){
            solve();
        }
    }
    return 0;
}
