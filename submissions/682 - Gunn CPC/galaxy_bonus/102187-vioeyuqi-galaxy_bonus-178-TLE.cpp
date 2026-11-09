#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pb push_back


char grid[300][300];
bool visited[300][300]={{0}};

int dx[4] = {0,1,-1,0};
int dy[4] = {1,0,0,-1};

void dfs(int n, int m, int x, int y, char c, int val){
    for (int i=0;i<4;i++){
        int nx = x+dx[i];
        int ny = y+dy[i];
        // cout << x << " " << y << " " << nx << " " << ny << endl;
        if (nx<0 or nx>=n or ny<0 or ny>=m or visited[nx][ny]){
            continue;
        }
        if (c==grid[nx][ny]){
            visited[nx][ny]=val;
            dfs(n,m,nx,ny,c,val);
        }
        if (grid[nx][ny]=='.'){
            visited[nx][ny]=val;
            dfs(n,m,nx,ny,'B',val);
            dfs(n,m,nx,ny,'R',val);
        }
    }
}

void calc(){
    int n,m,q;
    cin >> n >> m >> q;
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            char c;
            cin >> c;
            grid[i][j]=c;
        }
    }
    // visited[n-1][m-1]=1;
    // if (grid[n-1][m-1]=='.'){
    //     dfs(n,m,n-1,m-1,'R',1);
    //     dfs(n,m,n-1,m-1,'B',1);
    // }else{
    //     dfs(n,m,n-1,m-1,grid[n-1][m-1],1);
    // }

    // for (int i=0;i<n;i++){
    //     for (int j=0;j<m;j++){
    //         cout << visited[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    int cnt = 1;

    for (int i=0;i<q;i++){
        int x,y,fx,fy;
        cin >> x >> y >> fx >> fy;
        for (int i=0;i<n;i++){
            for (int j=0;j<m;j++){
                visited[i][j]=0;
            }
        }
        if (!visited[fx][fy]){
            visited[fx][fy]=cnt;
            if (grid[fx][fy]=='.'){
                dfs(n,m,fx,fy,'R',cnt);
                dfs(n,m,fx,fy,'B',cnt);
            }else{
                dfs(n,m,fx,fy,grid[fx][fy],cnt);
            }
        }
        if (visited[x][y] and visited[fx][fy]){
            cout << "YES" << "\n";
        }else{
            cout << "NO" << "\n";
        }
    }

    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            grid[i][j]='.';
            visited[i][j]=0;
        }
    }

}

signed main() {
    int t;
    cin >> t;
    while(t--){
        calc();
    }
}