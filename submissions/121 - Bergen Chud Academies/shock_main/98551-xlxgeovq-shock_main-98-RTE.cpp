#include<bits/stdc++.h>//I love Ogura Yui forever!
using namespace std;//Yui chan is so cute!
using ll=long long;

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

ll calc(Query f,int x,int y)
{
    ll ret=1ll*f.r*f.r-(1ll*(x-f.x)*(x-f.x)+1ll*(y-f.y)*(y-f.y))+1;
    // assert(ret>=1);
    return ret;
}
vector<int>ans[1000005];
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
        bool flag=false;
        if(n>m)
        {
            flag=true;
            swap(n,m);
            for(int i=1;i<=q;i++)
            {
                swap(a[i].x,a[i].y);
            }
        }
        for(int i=1;i<=n;i++)
            qu[i].clear(),ans[i].clear();
        for(int i=1;i<=q;i++)
        {
            int x=a[i].x,y=a[i].y,r=a[i].r;
            for(int j=x-r;j<=x+r;j++)
            {
                // assert(j>=1&&j<=n);
                ll d=(ll)sqrtl(1ll*r*r-1ll*(x-j)*(x-j));
                // assert(y-d>=1&&y+d<=m);
                qu[j].push_back(Query{y-d,y+d,i});
                
                // for(int k=y-d;k<=y+d;k++)
                // {
                //     assert(calc(a[i],j,k)>=1);
                // }
            }
        }

        for(int i=1;i<=n;i++)
        {
            ans[i].resize(m+5);
            for(int j=1;j<=m;j++)ans[i][j]=0;
            for(int j=1;j<=m+1;j++)fa[j]=j;
            for(auto it=qu[i].rbegin();it!=qu[i].rend();it++)
            {
                Query x=*it;
                int l=x.x,r=x.y,val=x.r;
                int pos=find(l);
                while(pos<=r)
                {
                    ans[i][pos]=calc(a[val],i,pos);
                    fa[pos]=find(pos+1);
                    pos=find(pos);
                }
            }
            qu[i].clear();
        }
        if(!flag)
        {
            for(int i=1;i<=n;i++)
            {
                for(int j=1;j<=m;j++)
                    printf("%d ",ans[i][j]);
                puts("");
            }
        }
        else
        {
            for(int j=1;j<=m;j++)
            {
                for(int i=1;i<=n;i++)
                    printf("%d ",ans[i][j]);
                puts("");
            }
        }
    }
    return 0;
}