#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define all(x) (x).begin(), (x).end()
#define forn(var,start,end) for(int var=start;var<end;var++)
#define X first
#define Y second

int n,m;
vector<string> v;
vector<vector<int>> adj;
vector<int> dist,st,en,k,ans;
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
const int inf=1LL<<60;

bool active(int r,int c,int z){
    if(v[r][c]=='.') return true;
    if(z==0) return v[r][c]=='B';
    return v[r][c]=='R';
}

void bfs(int s,int l,int r){
    int lo=2*n*l, hi=2*n*(r+1);
    fill(dist.begin()+lo,dist.begin()+hi,-1);

    queue<int> qu;
    qu.push(s);
    dist[s]=0;

    while(!qu.empty()){
        int x=qu.front();
        qu.pop();

        forn(i,0,(int)adj[x].size()){
            int y=adj[x][i];
            if(y<lo || y>=hi || dist[y]!=-1) continue;

            dist[y]=dist[x]+1;
            qu.push(y);
        }
    }
}

void divide(int l,int r,vector<int> ids){
    if(l>r || ids.empty()) return;
    int mid=(l+r)/2;

    forn(row,0,n){
        forn(z,0,2){
            if(!active(row,mid,z)) continue;
            int s=2*(mid*n+row)+z;
            bfs(s,l,r);

            forn(i,0,(int)ids.size()){
                int id=ids[i];
                int a=st[id]/(2*n), b=en[id]/(2*n);
                if(a<mid && b<mid) continue;
                if(a>mid && b>mid) continue;

                if(dist[st[id]]==-1) continue;

                int d=inf;
                if(dist[en[id]]!=-1) d=dist[en[id]];
                if(dist[en[id]+1]!=-1){
                    d=min(d,dist[en[id]+1]);
                }
                if(d!=inf){
                    ans[id]=min(ans[id],dist[st[id]]+d);
                }
            }
        }
    }

    vector<int> left,right;
    forn(i,0,(int)ids.size()){
        int id=ids[i];
        int a=st[id]/(2*n), b=en[id]/(2*n);

        if(a<mid && b<mid) left.push_back(id);
        if(a>mid && b>mid) right.push_back(id);
    }

    divide(l,mid-1,left);
    divide(mid+1,r,right);
}

void solve(){
    int t;
    cin>>t;

    while(t--){
        int q;
        cin>>n>>m>>q;
        v.resize(n);
        forn(i,0,n) cin>>v[i];

        adj.assign(2*n*m,vector<int>());
        dist.assign(2*n*m,-1);
        forn(r,0,n){
            forn(c,0,m){
                forn(z,0,2){
                    if(!active(r,c,z)) continue;
                    int x=2*(c*n+r)+z;

                    if(v[r][c]=='.'){
                        adj[x].push_back(x^1);
                    }

                    forn(i,0,4){
                        int nr=r+dx[i], nc=c+dy[i];
                        if(nr<0 || nr>=n || nc<0 || nc>=m) continue;
                        if(!active(nr,nc,z)) continue;

                        int y=2*(nc*n+nr)+z;
                        adj[x].push_back(y);
                    }
                }
            }
        }

        st.resize(q);
        en.resize(q);
        k.resize(q);
        ans.assign(q,inf);
        vector<int> ids(q);

        forn(i,0,q){
            int a,b,c,d;
            cin>>a>>b>>c>>d>>k[i];

            st[i]=2*(b*n+a);
            en[i]=2*(d*n+c);
            ids[i]=i;
        }

        divide(0,m-1,ids);

        forn(i,0,q){
            if(ans[i]<=k[i]) cout<<"YES\n";
            else cout<<"NO\n";
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}