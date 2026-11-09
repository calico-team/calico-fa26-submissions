#include<bits/stdc++.h>//I love Ogura Yui forever!
using namespace std;//Yui chan is so cute!
int n;
set<int>st[200005];

priority_queue<int,vector<int>,greater<int>>que;
int a[200005];
int las[200005];
vector<int>vec[200005];
int main()
{
    string s;
    cin>>s;
    if(s[0]=='F')
    {
        scanf("%d",&n);
        for(int x,y,i=1;i<n;i++)
        {
            scanf("%d%d",&x,&y);
            st[x].insert(y);
            st[y].insert(x);
        }
        for(int i=1;i<=n;i++)
        {
            if(st[i].size()==1)que.push(i);
        }
        int tot=0;
        for(int i=1;i<=n-2;i++)
        {
            int x=que.top();
            que.pop();
            int y=*st[x].begin();
            printf("%d ",y);
            tot^=y;
            st[y].erase(x);
            if(st[y].size()==1)
            {
                que.push(y);
            }
        }
        printf("%d 67\n",tot);
    }
    else
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)scanf("%d",&a[i]);
        if(a[n]!=-1&&a[n-1]!=-1)
        {
            int x=a[n-1];
            for(int i=1;i<=n-2;i++)
                if(a[i]!=-1)
                    x^=a[i];
            for(int i=1;i<=n-2;i++)
                if(a[i]==-1)
                    a[i]=x;
        }
        for(int j=1;j<=n;j++)las[j]=0;
        for(int j=1;j<=n-2;j++)las[a[j]]=j;
        for(int j=1;j<=n;j++)vec[las[j]+1].push_back(j);
        int u,v;
        for(int j=1;j<=n-2;j++)
        {
            for(int k:vec[j])que.push(k);
            u=a[j],v=que.top();
            if(u>v)swap(u,v);
            // printf("%d---%d\n",u,v);
            printf("%d %d\n",u,v);
            que.pop();
        }
        for(int k:vec[n-1])que.push(k);
        u=que.top();
        que.pop();
        v=que.top();
        que.pop();
        printf("%d %d\n",u,v);
        // printf("%d---%d\n",u,v);
        
    }
    return 0;
}