#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <cstring>
#include <queue>
#include <set>
#include <unordered_set>
using namespace std;
typedef pair<int, int> pi;
typedef pair<string, string> ps;
typedef pair<pi, char> pic;
typedef pair<char, char> pc;
#define endl "\n"
#define int long long
const int MOD = 1e9 + 7;
const int HASH = 197;
const int MM = 205;
const int MV = 1e6 + 5;
int T, N, M, Q;
char str[MM][MM];
int vis[MM][MM];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
void test(int sx, int sy, int N, int M, int foo){
    for (int k = 0; k < 4; ++k) {
        int nx = sx + dir[k][0], ny = sy + dir[k][1];
        //cout<<nx<<" "<<ny<<" "<<N<<" "<<M<<endl;
        //cout<<str[nx][ny]<<" "<<str[sx][sy]<<" "<<(str[nx][ny] == str[sx][sy] || (str[nx][ny] == '.' || str[sx][sx] == '.'))<<" "<<(nx >= 0 && nx < N && ny >= 0 && ny < M)<<endl;
        if (!vis[nx][ny] && nx >= 0 && nx < N && ny >= 0 && ny < M && (str[nx][ny] == str[sx][sy] || (str[nx][ny] == '.' || str[sx][sy] == '.'))) {
            vis[nx][ny] = foo; test(nx, ny, N, M, foo);
            //cout<<nx<<" "<<ny<<endl;
        }
    }
}
void solve(){
    int N, M, Q; memset(str, 0, sizeof(str)); memset(vis, false, sizeof(vis));
    cin >> N >> M >> Q;
    for (int i = 0; i < N; ++i) {
        string s; cin >> s;
        for (int j = 0; j < s.length(); j++) {
            str[i][j] = s[j];
        }
    }
    //vis[N-1][M-1] = true;
    //test(N-1, M-1, N, M, 0);
    int tmp = 1;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(vis[i][j] == 0){
                vis[i][j] = tmp;
                test(i, j, N, M, tmp);
                tmp++;
            }
        }
    }
    for (int i = 1; i <= Q; i++) {
        int sx, sy, ex, ey; cin >> sx >> sy >> ex >> ey;
        if (vis[sx][sy] == vis[ex][ey]) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
}
signed main() {
    cin >> T;
    for (int t = 1; t <= T; t++) {
        solve();
    }
}