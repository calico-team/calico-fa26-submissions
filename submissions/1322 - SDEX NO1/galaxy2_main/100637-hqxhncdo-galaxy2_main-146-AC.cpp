#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
const int dx[]={-1,1,0,0};
const int dy[]={0,0,-1,1};
const int INF=1000000000;
struct Query{
    int sr,sc,er,ec,idx;
    long long K;
};
int N,M,Q;
vector<string> g;
vector<Query> queries;
vector<string> ans;
vector<int> dist;
vector<int> q;
inline int get_id(int r,int c,int s,int M){
    return 2*(r*M+c)+s;
}
void bfs(int sr,int sc,int s,int L,int R){
    for(int r=0;r<N;r++){
        int first=get_id(r,L,0,M);
        int last=get_id(r,R,1,M);
        fill(dist.begin()+first,dist.begin()+last+1,INF);
    }
    q.clear();
    int ql=0;
    int start_id=get_id(sr,sc,s,M);
    dist[start_id]=0;
    q.push_back(start_id);
    while(ql<(int)q.size()){
        int u=q[ql];
        ql++;
        int pos=u/2;
        int s=u%2;
        int r=pos/M;
        int c=pos%M;
        int d=dist[u];
        for(int dir=0;dir<4;dir++){
            int nr=r+dx[dir];
            int nc=c+dy[dir];

            if(nr<0||nr>=N||nc<L||nc>R){
                continue;
            }

            char ch=g[nr][nc];
            bool ok=false;
            if(s==0){
                if(ch=='.'||ch=='B'){
                    ok=true;
                }
            }else{
                if(ch=='.'||ch=='R'){
                    ok=true;
                }
            }

            if(!ok){
                continue;
            }

            int v=get_id(nr,nc,s,M);
            if(dist[v]==INF){
                dist[v]=d+1;
                q.push_back(v);
            }
        }

        if(g[r][c]=='.'){
            int ns=s^1;
            int v=get_id(r,c,ns,M);
            if(dist[v]==INF){
                dist[v]=d+1;
                q.push_back(v);
            }
        }
    }
}
void solve(int L,int R,vector<int>& ids){
    if(L>R||ids.empty()){
        return;
    }
    int mid=(L+R)/2;

    for(int r=0;r<N;r++){
        for(int s=0;s<2;s++){
            if(s==0&&g[r][mid]=='R'){
                continue;
            }
            if(s==1&&g[r][mid]=='B'){
                continue;
            }

            bfs(r,mid,s,L,R);

            for(int i=0;i<(int)ids.size();i++){
                int qidx=ids[i];
                if(ans[qidx]=="YES"){
                    continue;
                }

                Query qq=queries[qidx];

                int start_id=get_id(qq.sr,qq.sc,0,M);
                int end_id0=get_id(qq.er,qq.ec,0,M);
                int end_id1=get_id(qq.er,qq.ec,1,M);

                int ds=dist[start_id];
                int d0=dist[end_id0];
                int d1=dist[end_id1];
                int de=min(d0,d1);

                if(ds!=INF&&de!=INF){
                    long long best=(long long)ds+de;
                    if(best<=qq.K){
                        ans[qq.idx]="YES";
                    }
                }
            }
        }
    }
    vector<int> left_ids;
    vector<int> right_ids;

    for(int i=0;i<(int)ids.size();i++){
        int qidx=ids[i];

        if(ans[qidx]=="YES"){
            continue;
        }
        Query qq=queries[qidx];

        if(qq.sc<mid&&qq.ec<mid){
            left_ids.push_back(qidx);
        }else if(qq.sc>mid&&qq.ec>mid){
            right_ids.push_back(qidx);
        }
    }
    solve(L,mid-1,left_ids);
    solve(mid+1,R,right_ids);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    int T;
    cin>>T;
    for(int t=0;t<T;t++){
        cin>>N>>M>>Q;

        g.resize(N);
        for(int i=0;i<N;i++){
            cin>>g[i];
        }
        queries.resize(Q);
        ans.assign(Q,"NO");
        int total=2*N*M;
        dist.assign(total,INF);
        q.clear();
        q.reserve(total);

        vector<int> ids;

        for(int qid=0;qid<Q;qid++){
            int sr,sc,er,ec;
            long long K;
            cin>>sr>>sc>>er>>ec>>K;
            Query qtmp;
            qtmp.sr=sr;
            qtmp.sc=sc;
            qtmp.er=er;
            qtmp.ec=ec;
            qtmp.idx=qid;
            qtmp.K=K;
            queries[qid]=qtmp;

            if(sr==er&&sc==ec){
                ans[qid]="YES";
            }else{
                ids.push_back(qid);
            }
        }

        solve(0,M-1,ids);

        string out;
        out.reserve(Q*5);
        for(int i=0;i<Q;i++){
            out+=ans[i];
            out+='\n';
        }
        cout<<out;
    }

    return 0;
}
