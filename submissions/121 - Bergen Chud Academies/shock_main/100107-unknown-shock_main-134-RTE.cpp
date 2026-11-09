#include<bits/stdc++.h>
using namespace std;

int fa[1000005];
int find(int x)
{
    if(x!=fa[x])fa[x]=find(fa[x]);
    return fa[x];
}

struct Query
{
    int x,y,r;
}a[1000005];

vector<Query>qu[1000005];

int T;
int n,m,q;

int calc(Query f,int x,int y)
{
    int ret=f.r*f.r-((x-f.x)*(x-f.x)+(y-f.y)*(y-f.y))+1;
    // assert(ret>=1);
    return ret;
}
int *ans[1005];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d",&n,&m,&q);
        for(int i=1;i<=q;i++)
        {
            scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].r);
            a[i].x++;
            a[i].y++;
        }
        for(int i=1;i<=n;i++)
            qu[i].clear();
        for(int i=1;i<=q;i++)
        {
            int x=a[i].x,y=a[i].y,r=a[i].r;
            for(int j=x-r;j<=x+r;j++)
            {
                int d=(int)sqrt(r*r-(x-j)*(x-j));
                qu[j].push_back(Query{y-d,y+d,i});
            }
        }

        for(int i=1;i<=n;i++)
        {
            ans[i]=new int[m+5];
            for(int j=1;j<=m;j++)ans[i][j]=0;
            for(int j=1;j<=m+1;j++)fa[j]=j;

            reverse(qu[i].begin(),qu[i].end());
            for(auto x:qu[i])
            {
                int l=x.x,r=x.y,val=x.r;
                // for(int j=l;j<=r;j++)
                // {
                //     if(!ans[i][j])
                //         ans[i][j]=calc(a[val],i,j);
                // }
                int pos=find(l);
                while(pos<=r)
                {
                    ans[i][pos]=calc(a[val],i,pos);
                    fa[pos]=pos+1;
                    pos=find(pos);
                }
            }
        }

        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=m;j++)
                printf("%d ",ans[i][j]);
            puts("");
        }
    }
    return 0;
}