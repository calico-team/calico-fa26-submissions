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

signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	// vladi();
	int t = 1;
	cin>>t;
	while(t--)moni();
}

struct DSU{
    vector<int> p;

    DSU(int n){
        p.resize(n);
        iota(all(p), 0);
    }

    int fnd(int x){
        if(p[x] == x)return x;
        return p[x] = fnd(p[x]);
    }

    bool upd(int a,int b){
        a = fnd(a);
        b = fnd(b);
        if(a == b)return 0;
        p[a] = b;
        return 1;
    }

    bool qry(int a,int b){
        return fnd(a) == fnd(b);
    }
};

bool ok(char a, char b){
    if(a == '.' || b == '.')return 1;
    return a == b;
}

void moni(){
	int n, m, q;
    cin>>n>>m>>q;
    string s[n];
    for(int i = 0;i < n;i++)cin>>s[i];

    auto get = [&](int a,int b)->int{
        return m * a + b;
    };

    DSU dsu(n * m);
    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            if(i && ok(s[i][j], s[i - 1][j]))dsu.upd(get(i, j), get(i - 1, j));
            if(j && ok(s[i][j], s[i][j - 1]))dsu.upd(get(i, j), get(i, j - 1));
        }
    }

    while(q--){
        int a, b, c, d;
        cin>>a>>b>>c>>d;
        if(dsu.qry(get(a, b), get(c, d)))cout<<"YES\n";
        else cout<<"NO\n";
    }
}
