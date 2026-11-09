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
    int N, M, K;
    cin >> N >> M >> K;
    vi A(N);
    cin >> A;
    vector<vi> adj(N);
    vi S;
    for(int i = 0; i < N; i++){
        if(A[i] == 0){
            S.push_back(i);
        }
        else{
            adj[A[i]-1].push_back(i);
        }
    }

    vi bfs;
    for(int i : S) bfs.push_back(i);
    for(int i = 0; i < N; i++){
        int v = bfs[i];
        for(int c : adj[v]){
            bfs.push_back(c);
        }
    }

    vi ch(N, 1);
    for(int i = N-1; i >= 0; i--){
        int v = bfs[i];
        for(int c : adj[v]){
            ch[v] += ch[c];
        }
    }
    //cout << ch << "\n";

    priority_queue<pii> pq;
    for(int i : S){
        pq.push(make_pair(ch[i], i));
    }

    int ans=0;
    for(int i = 0; i < M; i++){
        vi take;
        for(int j = 0; j < K && !pq.empty(); j++){
            pii p = pq.top();
            take.push_back(p.second);
            pq.pop();
        }
        ans += take.size();

        for(int v : take){
            for(int c : adj[v]){
                pq.emplace(ch[c], c);
            }
        }
    }
    cout << ans << endl;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int T=1;
    cin >> T;
    for(int i = 0; i < T; i++){
        process();
    }
       	 
} 

