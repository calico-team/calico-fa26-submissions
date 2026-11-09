#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
const int N = 210;
char a[N][N];
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
bool vis[N][N];
int CC[N][N];
int n, m;
bool check(int x, int y, char cur){
    if(x <= 0 || y <= 0 || x > n || y > m || vis[x][y]) return false;
    if(cur == '.' || a[x][y] == '.') return true;
    if(cur != a[x][y]) return false;
    return true;
}
void bfs(int startx, int starty, int id){
    queue<pii> q;
    q.push({startx, starty});
    vis[startx][starty] = true;
    CC[startx][starty] = id;
    while(!q.empty()){
        int curx = q.front().first;
        int cury = q.front().second;
        q.pop();
        for(int i = 0; i < 4; i++){
            if(check(curx+dx[i], cury+dy[i], a[curx][cury])){
                q.push({curx+dx[i], cury+dy[i]});
                vis[curx+dx[i]][cury+dy[i]] = true;
                CC[curx+dx[i]][cury+dy[i]] = id;
            }
        }
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while(T--){
        int q;
        cin >> n >> m >> q;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                cin >> a[i][j]; 
                vis[i][j] = false;
            }
        }
        int id = 0;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                if(vis[i][j] == true) continue;
                id++;
                bfs(i, j, id);
            }
        }
        while(q--){
            int startx, starty, endx, endy;
            cin >> startx >> starty >> endx >> endy;
            startx++; starty++; endx++; endy++;
            if(CC[startx][starty] == CC[endx][endy]){
                cout << "YES\n";
            }else{
                cout << "NO\n";
            }
        }
    }
    return 0;
}