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

struct DSU{
    vector<int> par;
    int N;
    vector<int> rk;

    DSU(int n): N(n){
        par = vector<int>(N);
        iota(par.begin(), par.end(), 0);
        rk = vector<int>(N, 1);
    }
    int find(int a){
        if(a == par[a]) return a;
        return (par[a] = find(par[a]));
    }
    void merge(int a, int b){
        a = find(a); b = find(b);
        if(a == b) return;
        if(rk[a] < rk[b]) swap(a, b);
        rk[a] += rk[b];
        par[b] = a;
    }
};

int N, M, Q;

int enc(int r, int c){
    int ind = r*M+c;
    //if(col == 1) ind += M*N;
    return ind;
}

bool connect(char a, char b){
    if(a == b) return true;
    return (a=='.' || b == '.');
}

void process(){
    cin >> N >> M >> Q;
    vector<string> grid(N);
    cin >> grid;

    DSU dsu(N*M*2);


    vector<pii> W;
    for(int i = 0; i < N; i++){
        for(int e = 0; e < M; e++){
            if(i > 0 && connect(grid[i][e], grid[i-1][e])){
                dsu.merge(enc(i,e),enc(i-1,e));
            }
            if(e > 0 && connect(grid[i][e], grid[i][e-1])){
                dsu.merge(enc(i,e),enc(i,e-1));
            }
        }
    }

    for(int i = 0; i < Q; i++){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if(dsu.find(enc(x1, y1)) == dsu.find(enc(x2, y2))){
            cout << "YES\n";
        }
        else{
            cout << "NO\n";
        }
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

