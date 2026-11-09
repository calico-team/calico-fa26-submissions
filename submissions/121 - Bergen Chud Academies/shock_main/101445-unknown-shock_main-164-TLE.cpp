#include<bits/stdc++.h>
using namespace std;

// int fa[1000005];
// int find(int x)
// {
//     if(x!=fa[x])fa[x]=find(fa[x]);
//     return fa[x];
// }

struct Query
{
    int x,y,r;
}a[1000005];

vector<pair<pair<int,int>,int>>qu[1000005];

int T;
int n,m,q;

int calc(Query f,int x,int y)
{
    int ret=1ll*f.r*f.r-(1ll*(x-f.x)*(x-f.x)+1ll*(y-f.y)*(y-f.y))+1;
    // assert(ret>=1);
    return ret;
}
int *ans[1000005];
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
        {
            qu[i].clear();
            ans[i]=new int[m+5];
            for(int j=1;j<=m;j++)ans[i][j]=0;
        }
        for(int i=1;i<=q;i++)
        {
            int x=a[i].x,y=a[i].y,r=a[i].r;
            for(int j=x-r;j<=x+r;j++)
            {
                int d=(int)sqrt(1ll*r*r-1ll*(x-j)*(x-j));
                // qu[j].push_back({{y-d,y+d},i});

                // for(int k=y-d;k<=y+d;k++)
                // {
                //     ans[j][k]=calc(a[i],j,k);
                // }
            }
        }

        for(int i=1;i<=q;i++)
        {
            int x=a[i].x,y=a[i].y,r=a[i].r;
            for(int j=x-r;j<=x+r;j++)
            {
                int d=(int)sqrt(1ll*r*r-1ll*(x-j)*(x-j));

                for(int k=y-d;k<=y+d;k++)
                {
                    ans[j][k]=calc(a[i],j,k);
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