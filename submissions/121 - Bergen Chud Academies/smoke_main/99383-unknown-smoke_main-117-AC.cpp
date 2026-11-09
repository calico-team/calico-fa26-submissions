#include<bits/stdc++.h>//I love Ogura Yui forever!
using namespace std;//Yui chan is so cute!
int n,r;
int a[100005];
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&r);
        int las=-1e9;
        bool ans=true;
        for(int i=1;i<=n;i++)
        {
            int x;
            scanf("%d",&x);
            if(x-las>=r*2)
            {
                las=x-r;
            }
            else if(x-las>=r)
            {
                las+=r;
            }
            else
            {
                ans=false;
            }
        }
        if(ans)
        {
            puts("YES");
        }
        else puts("NO");
    }
    return 0;
}