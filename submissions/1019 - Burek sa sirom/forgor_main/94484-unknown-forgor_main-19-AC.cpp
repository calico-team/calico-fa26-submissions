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
const int LOG = 20;

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
	string s;
    cin>>s;
    if(s == "FIRST")One();
    else Two();
}

vector<int> g[N];
int par[N];

void dfs(int x,int p){
    par[x] = p;
    for(auto u: g[x]){
        if(u == p)continue;
        dfs(u, x);
    }
}

void One(){
    int n ;
    cin>>n;
    for(int i = 1;i < n;i++){
        int a, b;
        cin>>a>>b;
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0, 0);
    int sum = 0;
    for(int i = 1;i < n;i++)sum += par[i];
    sum %= n;
    sum = n - sum;
    sum %= n;
    cout<<sum<<" ";
    for(int i = 1;i < n;i++)cout<<par[i]<<" ";
    cout<<'\n';
}


void Two(){
    int mi = 0;
    int n;
    cin>>n;
    int A[n];
    for(int i = 0;i < n;i++)cin>>A[i];
    for(int i = 0;i < n;i++){
        if(A[i] == -1)mi = i;
    }
    int sum = 0;
    for(int i = 0;i < n;i++){
        if(i != mi)sum += A[i];
    }
    sum %= n;
    sum = n - sum;
    sum %= n;
    A[mi] = sum;
    for(int i = 1;i < n;i++){
        cout<<i + 1<<" "<<A[i] + 1<<'\n';
    }
}