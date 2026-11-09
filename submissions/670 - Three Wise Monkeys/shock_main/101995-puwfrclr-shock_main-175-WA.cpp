#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef vector<double> vd;
typedef pair<int, int> pii;
typedef pair<pii, int> ppi;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pdd;

template <class T1, class T2>
istream& operator>>(istream& a, pair<T1, T2> &b){
    return (a >> b.first >> b.second);
}

template <class T>
istream& operator>>(istream& a, vector<T> &v){
    for(int i = 0; i < (int)v.size(); i++){
        a >> v[i];
    }
    return a;
}

template <class T1, class T2>
ostream& operator<<(ostream& a, pair<T1, T2> &b){
    return (a << b.first << " " << b.second);
}

template <class T>
ostream& operator<<(ostream& a, vector<T> &v){
    for(int i = 0; i < (int)v.size(); i++){
        a << v[i] << " ";
    }
    return a;
}


vector<pair<pii, int>> E;
vector<vi> grid;
vector<vi> indd;
int N, M;
ll calcP(int x, int y, int ind){
    ll dx = abs(x - E[ind].first.first);
    ll dy = abs(y - E[ind].first.second);
    return (ll)E[ind].second*E[ind].second - (dx*dx+dy*dy) + 1;
}

bool ok(int x, int y, int ind){
    ll c = calcP(x, y, ind);
    if(c <= 0 || x < 0 || y < 0 || x >= N || y >= M || indd[x][y] == ind || grid[x][y] != -1) return false;
    return true;
}

void process(){
    int Q;
    cin >> N >> M >> Q;
    grid = vector<vi>(N, vi(M, -1));
    indd = vector<vi>(N, vi(M, -1));

    E.clear();

    vector<vector<pii>> up(N, vector<pii>(M));
    vector<vector<pii>> down(N, vector<pii>(M));
    vector<vector<pii>> L(N, vector<pii>(M));
    vector<vector<pii>> R(N, vector<pii>(M));
    for(int i = 0; i < N; i++){
        for(int e = 0; e < M; e++){
            if(i > 0) up[i][e] = pii{i-1, e};
            else up[i][e] = pii{-1,-1};
            if(e > 0) L[i][e] = pii{i, e-1};
            else L[i][e] = pii{-1,-1};
            if(i+1 < N) down[i][e] = pii{i+1, e};
            else down[i][e] = pii{-1,-1};
            if(e+1 < M) R[i][e] = pii{i, e+1};
            else R[i][e] = pii{-1,-1};
        }
    }

    auto rem = [&](int x, int y){
        if(L[x][y].first != -1){
            R[L[x][y].first][L[x][y].second] = R[x][y];
        }
        if(R[x][y].first != -1){
            L[R[x][y].first][R[x][y].second] = L[x][y];
        }
        if(up[x][y].first != -1){
            down[up[x][y].first][up[x][y].second] = down[x][y];
        }
        if(down[x][y].first != -1){
            up[down[x][y].first][down[x][y].second] = up[x][y];
        }
    };

    for(int i = 0; i < Q; i++){
        int x, y, p;
        cin >> x >> y >> p;
        E.emplace_back(pii{x,y}, p);
    }
    reverse(E.begin(), E.end());


    for(int i = 0; i < Q; i++){
        queue<pii> q;
        q.push(E[i].first);
        {
            int x = E[i].first.first;
            int y = E[i].first.second;
            /*
            {
                q.push(pii{min(N-1, y+E[i].second), y});
                q.push(pii{max(0, x-E[i].second), y});
                q.push(pii{x, min(M-1, y+E[i].second)});
                q.push(pii{x, max(0, y-E[i].second)});
            }*/
            
            for(int e = 1; e <= E[i].second; e++){
                int C = calcP(x+e, y, i);
                if(x+e < N && C > grid[x+e][y]) q.push(pii{x+e,y});
                if(x-e >= 0 && C > grid[x-e][y]) q.push(pii{x-e,y});
                if(y+e < M && C > grid[x][y+e]) q.push(pii{x,y+e});
                if(y-e >= 0 && C > grid[x][y-e]) q.push(pii{x,y-e});
            }
        }
        while(!q.empty()){
            pii p = q.front();
            q.pop();
            int C = calcP(p.first, p.second, i);
            if(C <= 0) continue;
            if(grid[p.first][p.second] == -1){
                grid[p.first][p.second] = C;
                rem(p.first, p.second);
            }
            indd[p.first][p.second] = i;
            //cout << "q: " << i << " " << p << "\n";
            {
                pii pp = up[p.first][p.second];
                if(ok(pp.first, pp.second, i)){
                    indd[pp.first][pp.second] = i;
                    grid[pp.first][pp.second] = calcP(pp.first, pp.second, i);
                    rem(pp.first, pp.second);
                    q.push(make_pair(pp.first, pp.second));
                }
            }
            {
                pii pp = down[p.first][p.second];
                if(ok(pp.first, pp.second, i)){
                    indd[pp.first][pp.second] = i;
                    grid[pp.first][pp.second] = calcP(pp.first, pp.second, i);
                    rem(pp.first, pp.second);
                    q.push(make_pair(pp.first, pp.second));
                }
            }
            {
                pii pp = L[p.first][p.second];
                if(ok(pp.first, pp.second, i)){
                    indd[pp.first][pp.second] = i;
                    grid[pp.first][pp.second] = calcP(pp.first, pp.second, i);
                    q.push(make_pair(pp.first, pp.second));
                    rem(pp.first, pp.second);
                }
            }
            {
                pii pp = R[p.first][p.second];
                if(ok(pp.first, pp.second, i)){
                    indd[pp.first][pp.second] = i;
                    grid[pp.first][pp.second] = calcP(pp.first, pp.second, i);
                    rem(pp.first, pp.second);
                    q.push(make_pair(pp.first, pp.second));
                }
            }
        }
        /*
        cout << "printfrid\n";
    for(int j = 0; j < N; j++){
        for(int e = 0; e < M;e++){
            //if(grid[j][e] == -1) grid[j][e] = 0;
            cout << grid[j][e] << " ";
        }
        cout << endl;
    }*/
    }

    for(int i = 0; i < N; i++){
        for(int e = 0; e < M; e++){
            if(grid[i][e] == -1) grid[i][e] = 0;
            cout << grid[i][e] << " ";
        }
        cout << "\n";
    }

}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int T=1;
    cin >> T;
    for(int i = 0; i < T; i++){
        process();
    }
       	 
} 

