#include <bits/stdc++.h>
#include <ciso646>
#include <queue>
#define DEBUG false
#define int long long
const int inf = 1e12;
#define endl '\n'
using namespace std;
const int MOD = 1e9 + 7;
const int oi = 0; //toggle 0 for 0-index, toggle 1 for 1-index, toggle n for n-index
vector<int> factors;
vector<int> e1, sub;
vector<bool> visited, visited1;
vector<vector<int>> adj, connection;
vector<int> ans;
bool good = true;
int find(vector<int> &e, int x){
    return e[x] < 0 ? x : e[x] = find(e, e[x]);
    }
    void unite(vector<int> &e, int a, int b){
        a = find(e, a), b = find(e, b);
            if(a == b){
                    return;
                        }
                            if(e[a] > e[b]){
                                    swap(a, b);
                                        }
                                            e[a] += e[b];
                                                e[b] = a;
                                                }

                                                struct dsu{
                                                    vector<int> e;
                                                        dsu(int n){
                                                                e = vector<int>(n + 1, -1);
                                                                    }
                                                                        int get(int x){
                                                                                return e[x] < 0 ? x : e[x] = get(e[x]);
                                                                                    }
                                                                                        bool same_set(int a, int b){
                                                                                                return get(a)== get(b);
                                                                                                    }
                                                                                                        int size(int x){
                                                                                                                return -e[get(x)];
                                                                                                                    }
                                                                                                                        bool unite(int x, int y){
                                                                                                                                x = get(x), y = get(y);
                                                                                                                                        if(x == y){
                                                                                                                                                    return false;
                                                                                                                                                            }
                                                                                                                                                                    if(e[x] > e[y]){
                                                                                                                                                                                swap(x, y);
                                                                                                                                                                                        }
                                                                                                                                                                                                e[x] += e[y];
                                                                                                                                                                                                        e[y] = x;
                                                                                                                                                                                                                return true;
                                                                                                                                                                                                                    }
                                                                                                                                                                                                                    };

                                                                                                                                                                                                                    struct bin{ //Binary Indexed Tree / Fenwick Tree
                                                                                                                                                                                                                        /*
                                                                                                                                                                                                                            1 -> [1..1] -> 0001
                                                                                                                                                                                                                                2 -> [1..2] -> 0010
                                                                                                                                                                                                                                    3 -> [3..3] -> 0011
                                                                                                                                                                                                                                        4 -> [1..4] -> 0100
                                                                                                                                                                                                                                            5 -> [5..5] -> 0101
                                                                                                                                                                                                                                                6 -> [5..6] -> 0110
                                                                                                                                                                                                                                                    7 -> [7..7] -> 0111
                                                                                                                                                                                                                                                        8 -> [1..8] -> 1000
                                                                                                                                                                                                                                                            */
                                                                                                                                                                                                                                                                int n;
                                                                                                                                                                                                                                                                    vector<int> tree;
                                                                                                                                                                                                                                                                        bin(int n){
                                                                                                                                                                                                                                                                                this -> n = n;
                                                                                                                                                                                                                                                                                        tree = vector<int>(n + 1, 0);
                                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                                                void update(int i, int v){
                                                                                                                                                                                                                                                                                                        while(i <= n){
                                                                                                                                                                                                                                                                                                                    tree[i] += v;
                                                                                                                                                                                                                                                                                                                                i += i & -i; //i & -i gives the last set bit of i
                                                                                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                                                                                                int query(int i){
                                                                                                                                                                                                                                                                                                                                                        int sum = 0;
                                                                                                                                                                                                                                                                                                                                                                while(i > 0){
                                                                                                                                                                                                                                                                                                                                                                            sum += tree[i];
                                                                                                                                                                                                                                                                                                                                                                                        i -= i & -i; 
                                                                                                                                                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                                                                                                                                                        return sum;
                                                                                                                                                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                                                                                                                                                                int range_query(int l, int r){
                                                                                                                                                                                                                                                                                                                                                                                                                        return query(r)- query(l - 1);
                                                                                                                                                                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                                                                                                                                                                            };

                                                                                                                                                                                                                                                                                                                                                                                                                            void sieve(){
                                                                                                                                                                                                                                                                                                                                                                                                                                vector<bool> prime(1e6 + 1, true);
                                                                                                                                                                                                                                                                                                                                                                                                                                    prime[0] = prime[1] = false;
                                                                                                                                                                                                                                                                                                                                                                                                                                        for(int i = 2; i <= 1e4; i++){
                                                                                                                                                                                                                                                                                                                                                                                                                                                if(prime[i]){
                                                                                                                                                                                                                                                                                                                                                                                                                                                            factors.push_back(i);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                        for(int j = i * i; j <= 1e4; j += i){
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        prime[j] = false;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                }

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                class coord_dir{
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    public:
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            int x;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    int y;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            vector<int> dir = {0, 0, 0, 0};
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            };

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            void ldfs(int node, int pa, vector<bool> &visited, vector<vector<int>> &adj, int dop){   
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                visited[node] = true;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    sub[node] = 1;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        for(auto x : adj[node]){
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                if(!visited[x]){
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            ldfs(x, node, visited, adj, dop + 1);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        sub[node] += sub[x];
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    }   

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    bool acmp(const coord_dir &a, const coord_dir &b){
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        if(a.x == b.x){
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                return a.y < b.y;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        return a.x < b.x;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        }

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        bool cmpy(const coord_dir &a, const coord_dir &b){
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            if(a.y == b.y){
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    return a.x < b.x;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            return a.y < b.y;
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            }

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            int formula(int x1, int y1, int x2, int y2, vector<vector<int>> &prefix){
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                return(int)prefix[x1][y1] + prefix[x2 + 1][y2 + 1] - prefix[x1][y2 + 1] - prefix[x2 + 1][y1];
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                }

int state(char c){
    if(c == 'P'){
        return 0;
    }
    if(c == 'H'){
        return 1;
    }
    return 2;
}

struct ijsaddfgjasdg{
    int u;
    int w;
    int c;
};

bool cmp(const ijsaddfgjasdg &a, const ijsaddfgjasdg &b){
    return 0;
}
int dlkbasbsdaafsadlkflkafhksajhfkljfh(vector<ijsaddfgjasdg> &a, int d){
    int l = 0, r = a.size();
}
struct money{
    int x;
    int y;
    int len;
};

int find(int x, vector<int> &arr){
    return arr[x] == x ? x : arr[x] = find(arr[x], arr);
}

void dfs1(int x, int y, int n, int m, vector<vector<pair<int, int>>> &pa, vector<char> &res){
    while(pa[x][y].first != -1 and res.size() <= (n * m)){
        //cout<<boolalpha<<(pa[x][y].first != -1)<<endl;
        if(pa[x][y].first - x == -1){
            res.push_back('D');
        }
        if(pa[x][y].first - x == 1){
            res.push_back('U');
        }
        if(pa[x][y].second - y == -1){
            res.push_back('R');
        }
        if(pa[x][y].second - y == 1){
            res.push_back('L');
        }
        int x1 = x;
        x = pa[x][y].first, y = pa[x1][y].second;
        //cout<<x<<" "<<y<<endl;
    }
    //cout<<x<<" "<<y<<" is where A is"<<endl;
}

void dfs(vector<vector<int>> &anc){
    return;
}


bool dfs2(vector<vector<char>> &graph, queue<money> &call, vector<vector<int>> &ans, int n, int m, vector<vector<bool>> &visited, \
vector<vector<pair<int, int>>> &pa, vector<vector<int>> &ans1, vector<char> &res){
    while(!call.empty()){
        int x = call.front().x, y = call.front().y, len = call.front().len;
        call.pop();
        ans[x][y] = len;
        len++;
        if(x + 1 == n or x == 0 or y + 1 == m or y == 0){
            //cout<<x<<" "<<y<<endl;
            dfs1(x, y, n, m, pa, res);
            return true;
        }
        vector<pair<int, int>> nei = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for(int i = 0; i < 4; i++){
            pair<int, int> next = nei[i];
            int x1 = x + next.first, y1 = y + next.second;
            if(x1 < n and x1 >= 0 and y1 < m and y1 >= 0){
                if(graph[x1][y1] != '#' and !visited[x1][y1] and len < ans1[x1][y1]){
                    visited[x1][y1] = true;
                    pa[x1][y1] = {x, y};
                    call.push({x1, y1, len});
                }
            }
        }
    }
    return false;
}

int floordiv(int a, int b){
    if(b == 0){
        return 0;
    }
    int q = a / b, r = a % b;
    if(r != 0 and((a < 0)!=(b < 0))){
        q--;
    }
    return q;
}

int trinum(int n){
    return n *(n + 1)/ 2;
}

vector<int> jettism_is_worst_donut_smp_trapper(int n){
    vector<bool> primes(n + 1, true);
    vector<int> prime(n + 1, 1);
    primes[0] = primes[1] = false;
    for(int i = 2; i <= n; i++){
        if(primes[i]){
            prime[i] = i;
            for(int j = i * 2; j <= n; j += i){
                primes[j] = false;
                prime[j] = i;
            }
        }
    }
    for(int i = 0; i <= n; i++){
        //cout<<"["<<i<<"] = "<<prime[i]<<endl;
    }
    return prime;
}

vector<int> doggie_is_better_streamer_than_dr_donut(vector<int> &prime, int n){
    vector<int> factors;
    while(n > 1){
        factors.push_back(prime[n]);
        n /= prime[n];
    }
    return factors;
}

struct seg_tree{
    int n, sz;
    vector<int> seg;
    seg_tree(int n){
        this -> n = n;
        sz = 1;
        while(sz < n){
            sz <<= 1;
        }
        seg = vector<int> (2 * sz - 1, 0);
    }
    void initialize(vector<int> &arr, string &s){
        int sz = 1;
        while(sz < n){
            sz <<= 1;
        }
        for(int i = 0; i < n; i++){
            seg[sz - 1 + i] = arr[i];
        }
        for(int i = sz - 2; i >= 0; i--){
            seg[i] = min(seg[i * 2 + 1], seg[i * 2 + 2]);
        }
    }
    int find(int node, int l, int r, int ql, int qr){//len starts at 0
        if(r < ql or l > qr){
            return inf;
        }
        if(ql <= l and r <= qr){
            return seg[node];
        }
        int mid = (l + r) / 2;
        int left = find(2 * node + 1, l, mid, ql, qr);
        int right = find(2 * node + 2, mid + 1, r, ql, qr);
        return min(left, right);
    }
    int change(int node, int l, int r, int ql, int qr, vector<int> &arr){
        if(r < ql or l > qr){
            return inf;
        }
        if(ql <= l and r <= qr and l == r){
            seg[node] = min(seg[node], arr[l]);
            return seg[node];
        }
        int mid = (l + r) / 2;
        change(2 * node + 1, l, mid, ql, qr, arr);
        change(2 * node + 2, mid + 1, r, ql, qr, arr);
        seg[node] = min(seg[node * 2 + 1], seg[node * 2 + 2]);
        return seg[node];
    }
};

int bans, cans;

int ternary(int l, int r, int mode, int a, int b, int c, int cnt){
    if(r - l <= 2){
        int ans = l;
        for(int i = l + 1; i <= r; i++){
            if(mode == 2){
                int cur = abs((cnt * i) - c);
                int anscnt = abs((cnt * ans) - c);
                if(cur < anscnt){
                    ans = i;
                }
            }
            else if(mode == 1){
                int cur = abs((cnt * i) - b) + ternary(i, ceil(1e5 / cnt), 2, a, b, c, cnt);
                int anscnt = abs((cnt * ans) - b) + ternary(ans, ceil(1e5 / cnt), 2, a, b, c, cnt);
                if(cur < anscnt){
                    ans = i;
                }
                cans = ans;
            }
            else{
                int cur = abs(i - a) + ternary(1, ceil(1e5 / i), 1, a, b, c, i);
                int anscnt = abs(ans - a) + ternary(1, ceil(1e5 / ans), 1, a, b, c, ans);
                if(cur < anscnt){
                    ans = i;
                }
                bans = ans;
            }
            return ans;
        }
    }
    int m1 = l + (r - l) / 3;
    int m2 = r - (r - l) / 3;
    int cntm1, cntm2;
    if(mode == 2){
        cntm1 = abs((cnt * m1) - c);
        cntm2 = abs((cnt * m2) - c);
    }
    else if(mode == 1){
        cntm1 = abs((cnt * m1) - b) + ternary(m1, ceil(1e5 / cnt), 2, a, b, c, cnt);
        cntm2 = abs((cnt * m2) - b) + ternary(m2, ceil(1e5 / cnt), 2, a, b, c, cnt);
    }
    else{
        cntm1 = abs(m1 - a) + ternary(1, ceil(1e5 / cnt), 1, a, b, c, m1);
        cntm2 = abs(m2 - a) + ternary(1, ceil(1e5 / cnt), 1, a, b, c, m2);
    }
    if(cntm1 < cntm2){
        return ternary(l, m2, mode, a, b, c, cnt);
    }
    return ternary(m1, r, mode, a, b, c, cnt);
}

vector<int> special_input(int n){
    int a, b, c, x;
    cin>>x>>a>>b>>c;
    vector<int> arr = {0, x};
    for(int i = 2; i <= n; i++){
        int d = (arr[i - 1] * a + b) % c;
        arr.push_back(d);
    }
    return arr;
}

struct ilikecheese{
    int val;
    int mini;
    int maxi;
    int pa;
};


signed main(){
    if(DEBUG){
        freopen("time.in", "r", stdin);
        freopen("time.out", "w", stdout);
    }
    else{
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
    }
    int t;
    cin>>t;
    while(t--){
        int n, m;
        cin>>n>>m;
        vector<int> arr(n);
        int cnt = m, cnt1 = m;
        int maxi = 0;
        for(int i = 0; i < n; i++){
            cin>>arr[i];
            maxi = max(arr[i], maxi);
            //cout<<arr[i]<<" ";
        }
        bool good = true;
        int j = 0;
        for(int i = 0; i <= maxi; i++){
            if(cnt < m){
                cnt++;
            }
            else if(cnt1 < m){
                cnt1++;
            }
            if(i == arr[j]){
                if(cnt == m){
                    cnt = 0;
                }
                else if(cnt1 == m){
                    cnt1 = 0;
                }
                else{
                    good = false;
                    cout<<"NO"<<endl;
                    break;
                }
                j++;
            }
        }
        //cout<<endl;
        if(good){
            cout<<"YES"<<endl;
        }
    }
}
