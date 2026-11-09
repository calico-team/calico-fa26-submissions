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



void process1(){
    int N;
    cin >> N;

    vector<vi> adj(N);
    for(int i = 1; i < N; i++){
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vi bfs(1, 0);
    vi par(N);
    par[0] = 0;
    for(int i = 0; i < N; i++){
        int v = bfs[i];
        for(int c : adj[v]){
            if(c == par[v]) continue;
            par[c] = v;
            bfs.push_back(c);
        }
    }
    cout << bfs << "\n";
    cout << par << "\n";

    par[0] = 0;
    for(int i = 1; i < N; i++) par[0] ^= par[i];
    cout << par << endl;
}


void process2(){
    int N;
    cin >> N;
    vi A(N);
    cin >> A;
    int x=0;
    for(int i = 0; i < N; i++){
        if(A[i] != -1) x ^= A[i];
    }
    for(int i = 0; i < N; i++){
        if(A[i] == -1) A[i] = x;
    }

    for(int i = 1; i < N; i++){
        int u = A[i];
        int v = i;
        cout << u+1 << " " << v+1 << "\n";
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    

    string s;
    cin >> s;
    if(s == "FIRST"){
        process1();
    }
    else process2();
       	 
} 

