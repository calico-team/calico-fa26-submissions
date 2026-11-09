#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using si = set<int>;

bool good(char a,char b){
    if (a=='.' || b=='.')return true;
    if (a==b)return true;
    return false;
}

void solve(){
    int N,M,Q;cin>>N>>M>>Q;
    vector<string> rows(N);
    for (int i=0;i<N;i++){
        cin>>rows[i];
    }
    vector<pair<int,int>>normalSpots;
    vector<pair<int,int>>redSpots;
    vector<pair<int,int>>blueSpots;
    vector<pair<int,int>>spots;
    vector<vector<int>> group(N,vector<int>(M,-1));

    for (int i=0;i<N;i++){
        for (int j=0;j<M;j++){
            if (rows[i][j]=='.'){
                normalSpots.push_back({i,j});
            }
            if (rows[i][j]=='R'){
                redSpots.push_back({i,j});
            }
            if (rows[i][j]=='B'){
                blueSpots.push_back({i,j});
            }
            spots.push_back({i,j});
        }
    }
    vector<pair<int,int>>foundSpots;
    int currentIndex = 0;
    int groupNo = 0;
    while (foundSpots.size()<N*M){
        vector<pair<int,int>>newSpots(0);
        while (currentIndex<normalSpots.size() && group[normalSpots[currentIndex].first][normalSpots[currentIndex].second]!=-1){
            currentIndex++;
        }
        if (currentIndex==normalSpots.size())break;
        newSpots.push_back(normalSpots[currentIndex]);
        group[normalSpots[currentIndex].first][normalSpots[currentIndex].second]=groupNo;
        int spoti = 0;
        for (int i=0;i<newSpots.size();i++){
            int x = newSpots[i].first;
            int y = newSpots[i].second;
            if (x!=0 && group[x-1][y]==-1 && good(rows[x][y],rows[x-1][y])){
                newSpots.push_back({x-1,y});
                group[x-1][y] = groupNo;
            }
            if (x!=N-1 && group[x+1][y]==-1  && good(rows[x][y],rows[x+1][y])){
                newSpots.push_back({x+1,y});
                group[x+1][y] = groupNo;
            }
            if (y!=0 && group[x][y-1]==-1  && good(rows[x][y],rows[x][y-1])){
                newSpots.push_back({x,y-1});
                group[x][y-1] = groupNo;
            }
            if (y!=M-1 && group[x][y+1]==-1  && good(rows[x][y],rows[x][y+1])){
                newSpots.push_back({x,y+1});
                group[x][y+1] = groupNo;
            }
        }
        groupNo++;
    }
    while (Q--){
        int r1,c1,r2,c2;cin>>r1>>c1>>r2>>c2;
        if (group[r1][c1]==group[r2][c2]){
            cout<<"YES\n";
        } else {
            cout<<"NO\n";
        }
    }

}

int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    int t;cin>>t;
    while (t--)solve();
}
