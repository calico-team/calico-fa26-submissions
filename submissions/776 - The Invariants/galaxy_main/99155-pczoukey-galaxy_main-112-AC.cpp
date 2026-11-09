#include<bits/stdc++.h>
using namespace std;
struct DSU
{
    vector<int> parent,sz;
    DSU(int n)
    {
        parent.resize(n);
        sz.assign(n,1);
        iota(parent.begin(),parent.end(),0);

    }
    int find(int x)
    {
        if(parent[x]==x)
        {
            return x;
        }
        return parent[x]=find(parent[x]);

    }
    void unite(int a,int b)
    {
        a=find(a);
        b=find(b);
        if(a==b)
        {
            return;
        }
        if(sz[a]<sz[b])
        {
            swap(a,b);
        }
        parent[b]=a;
        sz[a]+=sz[b];
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while(T--)
    {
        int N,M,Q;
        cin>>N>>M>>Q;
        vector<string> G(N);
        for(int i=0;i<N;i++)
        {
            cin>>G[i];
        }
        int total=N*M;
        vector<int> blue(total,-1);
        vector<int> red(total,-1);
        int blueCnt=0,redCnt=0;
        int dr[]={-1,1,0,0};
        int dc[]={0,0,-1,1};
        auto bfs=[&](int sr,int sc,char mode,vector<int>& id,int comp)
        {
            queue<pair<int,int>> q;
            q.push({sr,sc});
            id[sr*M+sc]=comp;
            while(!q.empty())
            {
                auto [r,c]=q.front();
                q.pop();
                for(int d=0;d<4;d++)
                {
                    int nr=r+dr[d];
                    int nc=c+dc[d];
                    if(nr<0||nr>=N||nc<0||nc>=M)
                    {
                        continue;
                    }
                    int idx=nr*M+nc;
                    if(id[idx]!=-1)
                    {
                        continue;
                    }
                    if(G[nr][nc]==mode)
                    {
                        continue;
                    }
                    id[idx]=comp;
                    q.push({nr,nc});
                }
            }
        };
        for(int r=0;r<N;r++)
        {
            for(int c=0;c<M;c++)
            {
                int idx=r*M+c;
                if(G[r][c]!='R'&&blue[idx]==-1)
                {
                    bfs(r,c,'R',blue,blueCnt++);
                }
            }
        }
        for(int r=0;r<N;r++)
        {
            for(int c=0;c<M;c++)
            {
                int idx=r*M+c;
                if(G[r][c]!='B'&&red[idx]==-1)
                {
                    bfs(r,c,'B',red,redCnt++);
                }
            }
        }
        DSU dsu(blueCnt+redCnt);
        for(int r=0;r<N;r++)
        {
            for(int c=0;c<M;c++)
            {
                if(G[r][c]=='.')
                {
                    int idx=r*M+c;
                    dsu.unite(blue[idx],blueCnt+red[idx]);

                }
            }
        }
        while(Q--)
        {
            int rs,cs,re,ce;
            cin>>rs>>cs>>re>>ce;
            int start=rs*M+cs;
            int dest=re*M+ce;
            int srcComp=blue[start];
            int destComp;
            if(G[re][ce]=='R')
            {
                destComp=blueCnt+red[dest];
            }
            else
            {
                destComp=blue[dest];
            }
            if(dsu.find(srcComp)==dsu.find(destComp))
            {
                cout<<"YES\n";
            }
            else
            {
                cout<<"NO\n";
            }
        }
        
    }
    return 0;
}