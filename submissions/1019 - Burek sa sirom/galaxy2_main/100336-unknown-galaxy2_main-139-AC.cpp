#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define ar array
#define ld long double
#define all(A) A.begin(), A.end()


//const int MOD = 1e9 + 7;
const int MOD = 998244353;
const int N = 1e5 + 50;
const int B = 2;
const int INF = 1e17;;
const int LOG = 30;

void moni();
void vladi();



template<typename T>
void chmin(T &x, T y){x = min(x, y);}

template<typename T>
void chmax(T &x, T y){x = max(x, y);}

template<typename T>
void mm(T &x){
	x %= MOD;
	if(x < 0)x += MOD;
}

void One();
void Two();

signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	// vladi();
	int t;
    cin>>t;
    while(t--)moni();
}

int n, m, q;
string s[N];
int ans[N];
int lim[N];

int vis[11][N][2];
int dst[11][N][2];

int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};
int it = 1;

void f(int l,int r, vector<ar<int,5> >& Q){
    if(l > r || Q.empty())return;
    int mid = (l + r) / 2;
    for(int i = 0;i < n;i++){
        for(int z = 0;z < 2;z++){
            if(z == 0 && s[i][mid] == 'R')continue;
            if(z == 1 && s[i][mid] == 'B')continue;
            queue<ar<int,3> > q;
            q.push({i, mid, z});
            vis[i][mid][z] = it;
            dst[i][mid][z] = 0;
            while(q.size()){
                auto [x, y, t] = q.front();
                q.pop();
                if(s[x][y] == '.' && vis[x][y][t ^ 1] != it){
                    vis[x][y][t ^ 1] = it;
                    dst[x][y][t ^ 1] = dst[x][y][t] + 1;
                    q.push({x, y, t ^ 1});
                }
                for(int d = 0;d < 4;d++){
                    int nx = x + dx[d];
                    int ny = y + dy[d];
                    if(nx < 0 || nx >= n)continue;
                    if(ny < l || ny > r)continue;
                    if(t == 0 && s[nx][ny] == 'R')continue;
                    if(t == 1 && s[nx][ny] == 'B')continue;
                    if(vis[nx][ny][t] == it)continue;
                    vis[nx][ny][t] = it;
                    dst[nx][ny][t] = dst[x][y][t] + 1;
                    q.push({nx, ny, t});
                }
            }
            for(auto [a, b, c, d, i]: Q){
                if(vis[a][b][0] == it && vis[c][d][0] == it)chmin(ans[i], dst[a][b][0] + dst[c][d][0]);
                if(vis[a][b][0] == it && vis[c][d][1] == it)chmin(ans[i], dst[a][b][0] + dst[c][d][1]);
            }
            ++it;
        }

    }

    vector<ar<int,5> > L, R;
    for(auto [a, b, c, d, i]: Q){
        if(d < mid)L.push_back({a, b, c, d, i});
        if(b > mid)R.push_back({a, b, c, d, i});
    }
    f(l, mid - 1, L);
    f(mid + 1, r, R);
}

void moni(){
    cin>>n>>m>>q;
    for(int i = 0;i < n;i++)cin>>s[i];
    vector<ar<int,5> > Q;
    for(int i = 0;i < q;i++){
        ans[i] = INF;
        int a, b, c, d, k;
        cin>>a>>b>>c>>d>>k;
        Q.push_back({a, b, c, d, i});
        lim[i] = k;
    }
    f(0, m - 1, Q);
    for(int i = 0;i < q;i++){
        if(ans[i] <= lim[i])cout<<"YES\n";
        else cout<<"NO\n";
    }
}
