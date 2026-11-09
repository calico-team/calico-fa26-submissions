#include<bits/stdc++.h>
using namespace std;

int *fa[1000005];
int find(int i,int x)
{
    if(x!=fa[i][x])fa[i][x]=find(i,fa[i][x]);
    return fa[i][x];
}

struct Query
{
    int x,y,r;
}a[1000005];

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
            ans[i]=new int[m+5];
            fa[i]=new int[m+5];
            for(int j=1;j<=m;j++)ans[i][j]=0;
            for(int j=1;j<=m+1;j++)fa[i][j]=j;
        }
        for(int i=q;i>=1;i--)
        {
            int x=a[i].x,y=a[i].y,r=a[i].r;
            for(int j=x-r;j<=x+r;j++)
            {
                int d=(int)sqrt(1ll*r*r-1ll*(x-j)*(x-j));
                int l=y-d,r=y+d,val=i;

                int pos=find(j,l);
                while(pos<=r)
                {
                    ans[j][pos]=calc(a[val],j,pos);
                    fa[j][pos]=pos+1;
                    pos=find(j,pos);
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