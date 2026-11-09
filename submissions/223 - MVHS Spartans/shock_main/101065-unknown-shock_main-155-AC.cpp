#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

struct Quake{
    ll R;
    ll C;
    ll P;
};

void solve(){
    int N,M,Q;cin>>N>>M>>Q;
    vector<vector<ll>> nextEmpty(N,vector<ll>(M));
    vector<Quake> quakes;
    vector<vector<ll>> spots(N,vector<ll>(M,0));
    for (int i=0;i<N;i++){
        for (int j=0;j<M;j++){
            nextEmpty[i][j]=j+1;
        }
    }
    for (int i=0;i<Q;i++){
        quakes.emplace_back();
        int r,c,p;cin>>r>>c>>p;
        quakes[quakes.size()-1].R=r;
        quakes[quakes.size()-1].C=c;
        quakes[quakes.size()-1].P=p;
    }
    reverse(quakes.begin(),quakes.end());
    for (Quake quake:quakes){
        int currentc = quake.C;
        for (int row = quake.R-quake.P;row<=quake.R+quake.P;row++){
            if (row<quake.R){
                while ((currentc-quake.C-1)*(currentc-quake.C-1)+(row-quake.R)*(row-quake.R)<=quake.P*quake.P){
                    currentc--;
                }
            } else if (row==quake.R){
                currentc = quake.C-quake.P;
            } else {
                while ((currentc-quake.C)*(currentc-quake.C)+(row-quake.R)*(row-quake.R)>quake.P*quake.P){
                    currentc++;
                }
            }
            int coord = currentc;
            while ((coord-quake.C)<=(quake.C-currentc)){
                int oldCoord=coord;
                if (spots[row][coord]==0){
                    spots[row][coord] = quake.P*quake.P-(row-quake.R)*(row-quake.R)-(quake.C-coord)*(quake.C-coord)+1;
                    // if (spots[row][coord]<0)spots[row][coord]=0;
                    coord++;
                } else {
                    coord = nextEmpty[row][coord];
                }
                nextEmpty[row][oldCoord] = max(nextEmpty[row][oldCoord],quake.C+quake.C-currentc+1);
            }
        }
    }
    for (int i=0;i<N;i++){
        cout<<spots[i][0];
        for (int j=1;j<M;j++){
            cout<<" "<<spots[i][j];
        }
        cout<<"\n";
    }
}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int t;cin>>t;
    while (t--)solve();
}
