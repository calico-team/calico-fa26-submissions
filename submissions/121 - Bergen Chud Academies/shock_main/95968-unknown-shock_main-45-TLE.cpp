#include<bits/stdc++.h>//I love Ogura Yui forever!
using namespace std;//Yui chan is so cute!
using ll=long long;

struct segtree
{
    #define ls p*2
    #define rs p*2+1
    #define lss ls,l,mid
    #define rss rs,mid+1,r
    vector<int>tag;
    void resize(int n)
    {
        tag.resize(n*4+5);
    }
    void pushdown(int p)
    {
        if(tag[p])
        {
            tag[ls]=tag[p];
            tag[rs]=tag[p];
            tag[p]=0;
        }
    }
    void build(int p,int l,int r)
    {
        tag[p]=0;
        if(l==r)return;
        int mid=l+r>>1;
        build(lss);
        build(rss);
    }
    void change(int p,int l,int r,int x,int y,int z)
    {
        if(x<=l&&r<=y)
        {
            tag[p]=z;
            return;
        }
        pushdown(p);
        int mid=l+r>>1;
        if(x<=mid)change(lss,x,y,z);
        if(y>mid)change(rss,x,y,z);
    }
    int query(int p,int l,int r,int x)
    {
        if(l==r)return tag[p];
        pushdown(p);
        int mid=l+r>>1;
        if(x<=mid)return query(lss,x);
        else return query(rss,x);
    }
}akari[1005];


struct Query
{
    int x,y,r;
}a[20005];

int T;
int n,m,q;

ll calc(Query f,int x,int y)
{
    ll ret=1ll*f.r*f.r-(1ll*(x-f.x)*(x-f.x)+1ll*(y-f.y)*(y-f.y))+1;
    assert(ret>=1);
    return ret;
}
vector<int>ans[1005];
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
        {
            akari[i].resize(m);
            akari[i].build(1,1,m);
        }

        for(int i=1;i<=q;i++)
        {
            int x=a[i].x,y=a[i].y,r=a[i].r;
            for(int j=x-r;j<=x+r;j++)
            {
                ll d=sqrtl(1ll*r*r-1ll*(x-j)*(x-j));
                akari[j].change(1,1,m,y-d,y+d,i);
            }
        }
        for(int i=1;i<=n;i++)
        {
            ans[i].resize(m+1);
            for(int j=1;j<=m;j++)
            {
                int x=akari[i].query(1,1,m,j);
                if(x==0)ans[i][j]=0;
                else ans[i][j]=calc(a[x],i,j);
            }
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