#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--)
    { //man yall making me think bro im a washed olympiad my limits segment tree bro
    //this many ppl should not be able to do dsu in 5 minutes
        int n,k;
        cin>>n>>k;
        vector<int> ex;
        vector<int> ey;
        vector<int> nx;
        vector<int> ny;
        for(int i=0;i<n;i++)
        {
            int x,y,z;
            char d;
            cin>>x>>y>>z>>d;
            if(d=='E')
            {
                ex.push_back(x);
                ey.push_back(y);
            }
            else
            {
                nx.push_back(x);
                ny.push_back(y);
            }
        }
        int waterbye=0;
        for(int i=0;i<ex.size();i++)
        {
            for(int j=0;j<nx.size();j++)
            {
                if(ex[i]+ey[i]==nx[j]+ny[j]&&nx[j]-ex[i]>=0&&nx[j]-ex[i]<=k-1)
                {
                    waterbye++;
                }
            }
        }
        cout<<n*k-waterbye;
    }
}