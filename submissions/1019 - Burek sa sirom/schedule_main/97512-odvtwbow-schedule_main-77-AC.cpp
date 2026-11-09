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
int sz[N];
void dfs(int x){
    sz[x] = 1;
    for(auto u: g[x]){
        dfs(u);
        sz[x] += sz[u];
    }
}

void moni(){
    int n, m, k;
    cin>>n>>m>>k;
    int A[n];
    for(int i = 0;i < n; i++)g[i].clear();
    for(int i = 0;i < n;i++){
        cin>>A[i], --A[i];
        if(A[i] != -1)g[A[i]].push_back(i);
    }
    priority_queue<ar<int,2> > pq;
    for(int i = 0;i < n;i++){
        if(A[i] == -1){
            dfs(i);
            pq.push({sz[i], i});
        }
    }
    int ans = 0;
    while(m--){
        vector<int> v;
        for(int i = 0;i < k;i++){
            if(pq.empty())break;
            ans++;
            int x = pq.top()[1];
            pq.pop();
            for(auto u: g[x])v.push_back(u);
        }
        for(auto u: v)pq.push({sz[u], u});
    }
    cout<<ans<<'\n';
}
