// Success consists of going from failure to failure without loss of enthusiasm.
// ad hoc ad hoc go away, come again another day
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <iostream>
#define int long long
#define double long double
#pragma GCC optimize("Ofast,unroll-loops")
using namespace std;
struct pi{
    int x,y;
};
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t > 0){
        int n,m,z;
        cin >> n >> m >> z;
        vector<string>grid(n);
        for(int i = 0; i < n; i++)cin >> grid[i];
        vector<vector<int>>type(n, vector<int>(m, -1));
        vector<vector<int>>dir = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        int cc = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(type[i][j] == -1){
                    queue<pi>q;
                    type[i][j] = cc;
                    q.push({i,j});
                    while(!q.empty()){
                        pi cur = q.front();
                        for(int k = 0; k < 4; k++){
                            int cx = cur.x+dir[k][0], cy = cur.y+dir[k][1];
                            if(cx >= 0 && cx < n && cy >= 0 && cy < m && type[cx][cy] == -1 && (grid[cur.x][cur.y] == '.' || grid[cx][cy] == '.' || grid[cur.x][cur.y] == grid[cx][cy])){
                                type[cx][cy] = cc;
                                q.push({cx,cy});
                            }
                        }
                        q.pop();
                    }
                    cc++;
                }
            }
        }
        for(int i = 0; i < z; i++){
            int x1,y1,x2,y2;
            cin >> x1 >> y1 >> x2 >> y2;
            if(type[x1][y1] == type[x2][y2])cout << "YES\n";
            else cout << "NO\n";
        }
        t--;
    }
}