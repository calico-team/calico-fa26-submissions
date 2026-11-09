#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<ll>;

struct Drone{
    int X;
    int Y;
    char D;
};

bool comp(Drone a,Drone b){
    return a.X<b.X;
}

void solve(){
    ll N,K;cin>>N>>K;
    ll total = N*K;
    vector<vector<Drone>> droneList(2e5+1);
    set<string> drones;
    for (int i=0;i<N;i++){
        int x,y,z;char d;cin>>x>>y>>z>>d;
        string string = to_string(x)+" "+to_string(y)+" "+d;
        if (drones.count(string)){
            total-=K;
            continue;
        }
        drones.insert(string);
        droneList[x+y].emplace_back();
        droneList[x+y][droneList[x+y].size()-1].X=x;
        droneList[x+y][droneList[x+y].size()-1].Y=y;
        droneList[x+y][droneList[x+y].size()-1].D=d;
    }
    for (vector<Drone> diag:droneList){
        sort(diag.begin(),diag.end(),comp);
        int Es = 0;
        int minDrone=0;
        for (Drone drone:diag){
            if (drone.X-diag[minDrone].X>=K){
                Es--;minDrone++;
            }
            if (drone.D=='E'){
                Es++;
            }
            else{
                total-=Es;
            }
        }
    }
    cout<<total<<"\n";
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int t;cin>>t;
    while (t--)solve();
}
