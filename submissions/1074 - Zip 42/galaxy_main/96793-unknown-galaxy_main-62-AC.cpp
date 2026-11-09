//
// Created by User on 11/8/2026.
//

#include "bits/stdc++.h"
using namespace std;

static char grid[205][205];
static bool visited[205][205];

static int dirs[4][2]={
    {1,0},{0,1},{-1,0},{0,-1}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int cases;
    cin>>cases;
    while (cases>0) {
        cases--;

        int rows, cols, queries;
        cin>>rows>>cols>>queries;

        memset(grid,0,sizeof grid);
        memset(visited,false,sizeof visited);

        for (int i=0; i<rows; i++) {
            string s;
            cin>>s;
            for (int j=0; j<cols; j++) {
                grid[i][j]=s[j];
            }
        }
        //start at end
        queue<pair<int,int>> q;
        q.emplace(rows-1,cols-1);
        visited[rows-1][cols-1]=true;
        while (!q.empty()) {
            auto curr=q.front();
            q.pop();
            for (int i=0; i<4; i++) {
                int dr=dirs[i][0];
                int dc=dirs[i][1];
                int nr=dr+curr.first;
                int nc=dc+curr.second;

                if (nr<0 || nc<0 || nr>=rows || nc>=cols) {
                    continue;
                }
                if (visited[nr][nc]) {
                    continue;
                }
                if (grid[curr.first][curr.second]=='R' && grid[nr][nc]=='B'
                    || grid[curr.first][curr.second]=='B' && grid[nr][nc]=='R') {
                    continue;
                }
                visited[nr][nc]=true;
                q.emplace(nr,nc);
            }
        }
        for (int i=0; i<queries; i++) {
            int s1,s2,e1,e2;
            cin>>s1>>s2>>e1>>e2;
            if (visited[s1][s2]) {
                cout<<"YES"<<"\n";
            }else {
                cout<<"NO"<<"\n";
            }
        }
    }
}