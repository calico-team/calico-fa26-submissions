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



void process(){
    int N, M, Q;
    cin >> N >> M >> Q;
    vector<vi> grid(N, vi(M, -1));
    vector<vi> indd(N, vi(M, -1));

    vector<pair<pii, int>> E;

/*
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
    }*/

    for(int i = 0; i < Q; i++){
        int x, y, p;
        cin >> x >> y >> p;
        E.emplace_back(pii{x,y}, p);
    }
    //reverse(E.begin(), E.end());

    auto calcP = [&](int x, int y, int ind){
        ll dx = abs(x - E[ind].first.first);
        ll dy = abs(y - E[ind].first.second);
        return (ll)E[ind].second*E[ind].second - (dx*dx+dy*dy) + 1;
    };

    auto ok = [&](int x, int y, int ind){
        ll c = calcP(x, y, ind);
        if(c <= 0 || x < 0 || y < 0 || x >= N || y >= M || indd[x][y] == ind) return false;
        return true;
    };

    for(int i = 0; i < Q; i++){
        queue<pii> q;
        q.push(E[i].first);
        while(!q.empty()){
            pii p = q.front();
            q.pop();
            //if(grid[p.first][p.second] != -1) continue;
            grid[p.first][p.second] = calcP(p.first, p.second, i);
            indd[p.first][p.second] = i;
            if(ok(p.first-1, p.second, i)){
                indd[p.first-1][p.second] = i;
                q.push(make_pair(p.first-1, p.second));
            }
            if(ok(p.first+1, p.second, i)){
                indd[p.first+1][p.second] = i;
                q.push(make_pair(p.first+1, p.second));
            }
            if(ok(p.first, p.second-1, i)){
                indd[p.first][p.second-1] = i;
                q.push(make_pair(p.first, p.second-1));
            }
            if(ok(p.first, p.second+1, i)){
                indd[p.first][p.second+1] = i;
                q.push(make_pair(p.first, p.second+1));
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
        cout << endl;
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

