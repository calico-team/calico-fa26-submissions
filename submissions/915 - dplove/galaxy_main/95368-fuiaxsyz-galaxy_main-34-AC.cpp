#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<algorithm>
#include<cmath>
#include<climits>
#include<string>
#include<numeric>
#include<deque>
using namespace std;

#define int long long
#define vi vector<int>
#define pii pair<int,int>
#define yes cout<<"YES\n"
#define no cout<<"NO\n"
#define all(x) x.begin(),x.end()
#define ull unsigned long long
#define vs vector<string>

const int INF = 1e18;
const int modx = 1e9 + 7;
const int maxn = 2e5 + 1;

int modadd(int a, int b, int m = modx){ return (a+b)%m; }
int modmultiply(int a, int b,int m = modx){ return (a*b)%m; }
int modsubtract(int a, int b,int m = modx){ return (a-b+m)%m; }

int binpow(int base, int expo, int m = modx){
  if(expo == 0) return 1;
  if(expo == 1) return base%m;

  int temp = binpow(base,expo/2,m);
  int extra = (expo & 1) ? base : 1;

  return modmultiply(modmultiply(temp,temp,m),extra,m);
}

int modinverse_prime(int b, int m = modx){
  return binpow(b,m-2,m);
}

// Combinatorics

#if 0
   int fact[maxn+1];
   int inverse_fact[maxn+1];

   void precompute(){
    fact[0] = 1;
    inverse_fact[0] = 1;

    for(int i = 1; i <= maxn; i++) fact[i] = modmultiply (fact[i-1],i);
    for(int i = 1; i <= maxn; i++) inverse_fact[i] = modmultiply (inverse_fact[i-1],modinverse_prime(i));
   }

   int nCr(int n, int r){
    return modmultiply(fact[n], modmultiply(inverse_fact[r], inverse_fact[n-r]));
   }

   int nPr(int n, int r){
      return modmultiply(fact[n],inverse_fact[n - r]);
   }

   int nCr_small_r(int n, int r){
    if(r == 0 || r == n) return 1;
    r = min(r, n - r);
    int res = 1;
    for(int i = 0; i < r; i++){
        res = modmultiply(res, n - i);
        res = modmultiply(res, modinverse_prime(i + 1));
    }
    return res;
   }
#endif

// Binary Lifting

#if 0
struct binary_lifting{
   int n;
   vector<vector<int>> g;
   vector<vector<int>> parents;
   vector<int> dep;
   int LOG = 21;

   void dfs(int cur, int par){
     dep[cur] = (par == -1) ? 0 : dep[par] + 1;
     parents[cur][0] = par;
     for(int i = 1; i < LOG; i++){
      int mid = parents[cur][i-1];
      if(mid != -1) parents[cur][i] = parents[mid][i-1];
     }
     for(int c : g[cur]){
      if(c != par) dfs(c,cur);
     }
   }

   binary_lifting(vector<vector<int>> &adj_list){
    n = adj_list.size();
    g = adj_list;
    parents.assign(n,vector<int>(LOG,-1));
    dep.assign(n,0);
    dfs(0,-1);
   }

   int kPar(int x, int k){
    for(int i = 0; i < LOG; i++){
      if(x == -1) return -1;
      if((k >> i) & 1) x = parents[x][i];
    }
    return x;
   }

   int lca(int a, int b){
    if(dep[a] < dep[b]) swap(a,b);
    a = kPar(a,dep[a] - dep[b]);
    if(a == b) return a;
    for(int i = LOG - 1; i>=0; i--){
      if(parents[a][i] != parents[b][i]){
        a = parents[a][i];
        b = parents[b][i];
      }
    }
    return parents[a][0];
   }
};
#endif

// DSU

#if 0
struct DSU{
    int n; vector<int> parents; vector<int> sizes;

    DSU(int sizex){
        n = sizex;
        parents.resize(n);
        sizes.assign(n,1);
        for(int i = 0; i < n; i++) parents[i] = i;
    }

    int fset(int a){return (parents[a] == a) ? a : parents[a] = fset(parents[a]);}
    bool iset(int a, int b){return fset(a) == fset(b);}
    void uset(int a, int b){
        a = fset(a); b = fset(b); if(a == b) return; if(sizes[a] < sizes[b]) swap(a,b);
        parents[b] = a; sizes[a] += sizes[b];
    }
};
#endif

//Segtree with Lazy Propogation

#if 0
struct segtree{
  int n; vector<int> arr; vector<int> lazy;
  int a_id = 0;
  int lz_id = 0;
  int combine(int a, int b){return a+b;}
  int lz_combine(int a, int b){return a+b;}
  int apply(int nv, int lzv, int len){return nv + (lzv * len);}
  int upd(int lzv, int v){return lzv + v;}

  segtree() {}
  segtree(int sizex){
    n = 1; while(n < sizex) n<<=1;
    arr.assign(2*n,a_id);
    lazy.assign(2*n,lz_id);
  }

  void build(vector<int> &init, int x, int lx, int rx){
    if(rx - lx == 1){
        if(lx < (int)init.size()) arr[x] = init[lx];
        return;
    }
    int m = (lx+rx)>>1; build(init,2*x+1,lx,m); build(init,2*x+2,m,rx);
    arr[x] = combine(arr[2*x+1],arr[2*x+2]);
  }

  void propagate(int x, int lx, int rx){
    arr[x] = apply(arr[x],lazy[x],rx - lx);
    if(rx - lx > 1){
       lazy[2*x+1] = lz_combine(lazy[2*x+1],lazy[x]);
       lazy[2*x+2] = lz_combine(lazy[2*x+2],lazy[x]);
    }
    lazy[x] = lz_id;
  }

  void update(int i, int j, int v, int x, int lx, int rx){
    propagate(x,lx,rx);
    if(i <= lx && rx <= j){
        lazy[x] = upd(lazy[x],v);
        propagate(x,lx,rx);
        return;
    }
    if(i >= rx || j <= lx) return;
    int m = (lx+rx)>>1; update(i,j,v,2*x+1,lx,m); update(i,j,v,2*x+2,m,rx);
    arr[x] = combine(arr[2*x+1],arr[2*x+2]);
  }

  int query(int i, int j, int x, int lx, int rx){
    propagate(x,lx,rx);
    if(i <= lx && rx <= j) return arr[x];
    if(i >= rx || j <= lx) return a_id;
    int m = (lx+rx)>>1; 
    return combine(query(i,j,2*x+1,lx,m),query(i,j,2*x+2,m,rx));
  }

  void build(vector<int> &init){build(init,0,0,n);}
  void update(int i, int j, int v){update(i,j,v,0,0,n);}
  int query(int i, int j){return query(i,j,0,0,n);}
};
#endif

// Heavy-Light Decomposition

#if 0
struct HLD{
 int n; vector<int> pos,par,dep,heavy,head; int cur_pos = 0; segtree st;

 int dfs(int u, vector<vector<int>> &g){
  int size = 1, max_sub = 0;
  for(int v : g[u]){
    if(v != par[u]){
      par[v] = u;
      dep[v] = dep[u] + 1;
      int cur_v_size = dfs(v,g);
      size+=cur_v_size;
      if(cur_v_size > max_sub){
        max_sub = cur_v_size;
        heavy[u] = v;
      }
    }
  }
  return size;
 }

 void decompose(int v, int h, vector<vector<int>> &g){
  pos[v] = cur_pos++;
  head[v] = h;
  if(heavy[v] != -1) decompose(heavy[v],h,g);
  for(int c : g[v]){
    if(c!=par[v] && c!= heavy[v]) decompose(c,c,g);
  }
 }

 HLD(vector<vector<int>> &g){
  n = g.size();
  pos.resize(n);
  par.assign(n,-1);
  dep.assign(n,0);
  head.resize(n);
  heavy.assign(n,-1);
  st = segtree(n);
  par[0] = -1;
  dep[0] = 0;
  dfs(0,g);
  decompose(0,0,g);
 }

 int query(int a, int b){
  int res = st.a_id;
  while(head[a] != head[b]){
      if(dep[head[a]] > dep[head[b]]) swap(a,b);
      res = st.combine(res,st.query(pos[head[b]],pos[b] + 1));
      b = par[head[b]];
  }
  if(dep[a] > dep[b]) swap(a,b);
  res = st.combine(res,st.query(pos[a],pos[b] + 1));
  return res;
 }

 void point_update(int i, int v){
  st.update(pos[i],pos[i]+1,v);
 }

 void update(int a, int b,int v){
  while(head[a] != head[b]){
      if(dep[head[a]] > dep[head[b]]) swap(a,b);
      st.update(pos[head[b]],pos[b]+1,v);
      b = par[head[b]];
  }
  if(dep[a] > dep[b]) swap(a,b);
  st.update(pos[a],pos[b]+1,v);
 }
};
#endif

int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

void solve(){
  int n, m, q;
  cin >> n >> m >> q;

  vs grid(n);
  for(int i = 0; i < n; i++){
    cin >> grid[i];
  }

  auto valid = [&](int r, int c, int mode){
    if(r < 0 || r >= n || c < 0 || c >= m) return false;
    char ch = grid[r][c];
    if(mode == 0) return (ch == '.' || ch == 'B');
    return (ch == '.' || ch == 'R');
  };

  vector<vector<vi>> comp(n, vector<vi>(m, vi(2, -1)));
  int comp_id = 0;

  for(int i = 0; i < n; i++){
    for(int j = 0; j < m; j++){
      for(int mode = 0; mode < 2; mode++){
        if(valid(i, j, mode) && comp[i][j][mode] == -1){
          queue<pair<pii, int>> q;
          q.push({{i, j}, mode});
          comp[i][j][mode] = comp_id;

          while(!q.empty()){
            auto cur = q.front();
            q.pop();

            int r = cur.first.first;
            int c = cur.first.second;
            int cur_mode = cur.second;

            for(int d = 0; d < 4; d++){
              int nr = r + dr[d];
              int nc = c + dc[d];
              if(valid(nr, nc, cur_mode) && comp[nr][nc][cur_mode] == -1){
                comp[nr][nc][cur_mode] = comp_id;
                q.push({{nr, nc}, cur_mode});
              }
            }

            if(grid[r][c] == '.'){
              int next_mode = 1 - cur_mode;
              if(comp[r][c][next_mode] == -1){
                comp[r][c][next_mode] = comp_id;
                q.push({{r, c}, next_mode});
              }
            }
          }
          comp_id++;
        }
      }
    }
  }

  while(q--){
    int r_start, c_start, r_end, c_end; cin >> r_start >> c_start >> r_end >> c_end;

    int start_comp = comp[r_start][c_start][0];
    int end_comp = -1;

    if(grid[r_end][c_end] == 'R'){
      end_comp = comp[r_end][c_end][1];
    } else {
      end_comp = comp[r_end][c_end][0];
    }

    if(start_comp != -1 && start_comp == end_comp){
      yes;
    } else {
      no;
    }
  }
}

int32_t main(){
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  
  int t; cin>>t;

  while(t--){
    solve();
  }
}