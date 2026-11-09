#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(){
    int T; cin >> T;
    while(T--){
        int N, M, Q; cin >> N >> M >> Q;
        string G[N];
        
        for(int i = 0; i < N; i++){
            cin >> G[i];
        }
        
        int visited[N][M];
        memset(visited, 0, sizeof(visited));
        
        int color = 0;
        int xMove[4] = {-1, 0, 0, 1};
        int yMove[4] = {0, -1, 1, 0};
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                if(visited[i][j]) 
                    continue;
                    
                queue<pair<int, int>> q;
                q.push({i, j});
                color++;
                while(!q.empty()){    
                    int x = q.front().first, y = q.front().second;
                    q.pop();
                    
                    if(visited[x][y]) 
                        continue;
                    visited[x][y] = color;
                    for(int k = 0; k < 4; k++){
                        if(x + xMove[k] < N && x + xMove[k] >= 0 && y + yMove[k] < M && y + yMove[k] >= 0 && !visited[x + xMove[k]][y + yMove[k]] && (G[x][y] == '.' || G[x + xMove[k]][y + yMove[k]] == '.' || G[x][y] == G[x + xMove[k]][y + yMove[k]])){
                            q.push({x + xMove[k], y + yMove[k]});
                        }
                    }
                }
                    
            }
        }
        
        for(int query = 0; query < Q; query++){
            int Rstart, Cstart, Rend, Cend;
            cin >> Rstart >> Cstart >> Rend >> Cend;
            cout << (visited[Rstart][Cstart] == visited[Rend][Cend] ? "YES\n" : "NO\n");
        }
        
        
    }
    return 0;
}