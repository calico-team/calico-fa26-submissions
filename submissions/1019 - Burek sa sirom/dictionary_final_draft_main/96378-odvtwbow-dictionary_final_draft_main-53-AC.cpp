#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define ar array
#define ld long double
#define all(A) A.begin(), A.end()


//const int MOD = 1e9 + 7;
const int MOD = 998244353;
const int N = 1e6 + 50;
const int B = 2;
const int INF = 40;
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
struct Node {
    Node *b[2];
    int cnt;
    Node() {
        b[0] = b[1] = nullptr;
        cnt = 0;
    }
};

void add(Node *k, int x, int i, int v) {
    k->cnt += v;
    if (i == -1) return;
    bool b = (1 << i) & x;
    if (!k->b[b]) k->b[b] = new Node();
    add(k->b[b], x, i - 1, v);
}

int qry(Node *k, int x, int i) {
    if (!k || i == -1) return 0;
    bool b = (1 << i) & x;
    if (k->b[b ^ 1] && k->b[b ^ 1]->cnt)return (1 << i) + qry(k->b[b ^ 1], x, i - 1);
    return qry(k->b[b], x, i - 1);
}
int ans[N];
vector<int> g[N];
bool del[N];

int A[N], V[N];

void dfs(int x,int v, Node *trie){
    ans[x] = qry(trie, v, LOG);
    add(trie, v, LOG, 1);
    for(auto u: g[x]){
        if(del[u])continue;
        dfs(u, v ^ V[u], trie);
    }
    add(trie, v, LOG, -1);
}

void moni(){
    int n;
    cin>>n;
    for(int i = 0;i < n;i++){
        g[i].clear();
        del[i] = 0;
    }   
    int deg[n] = {0};  
    for(int i = 0;i < n;i++){
        cin>>A[i], --A[i];
        g[A[i]].push_back(i);
        deg[A[i]]++;
    }
    for(int i = 0;i < n;i++)cin>>V[i];
    queue<int> q;
    for(int i = 0;i < n;i++){
        if(!deg[i])q.push(i);
    }
    while(q.size()){
        int x = q.front();
        q.pop();
        deg[A[x]]--;
        if(!deg[A[x]])q.push(A[x]);
    }
    for(int i = 0;i < n;i++){
        if(deg[i])del[i] = 1;
    }
    bool vis[n] = {0};
    int pref[n]; 
    for(int i = 0;i < n;i++){
        if(vis[i])continue;
        if(!del[i])continue;
        int u = A[i];
        vector<int> C = {i};
        while(u != i){
            C.push_back(u);
            u = A[u];
        }
        for(auto u: C)vis[u] = 1;
        Node *t = new Node();
        int z = 0;
        int tot = 0;
        for(auto u: C){
            pref[u] = z;
            z ^= V[u];
        }
        for(auto u: C){
            add(t, pref[u], LOG, 1);
            add(t, z ^ pref[u], LOG, 1);    
        }
        for(auto u: C)dfs(u, pref[u], t);
    }
    for(int i = 0;i < n;i++)cout<<ans[i]<<" ";
    cout<<'\n';
}
