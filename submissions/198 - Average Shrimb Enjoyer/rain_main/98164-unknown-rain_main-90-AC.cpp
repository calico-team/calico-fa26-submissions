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
        int n,k;
        cin>>n>>k;
        vector<vector<int> >e(200001);
        vector<int> nsum;
        vector<int> xig;
        for(int i=0;i<n;i++)
        {
            int x,y,z;
            char d;
            cin>>x>>y>>z>>d;
            if(d=='E')
            {
                e[x+y].push_back(x);
            }
            else
            {
                nsum.push_back(x+y);
                xig.push_back(x);
            }
        }
        for(int s=0;s<=200000;s++)
        {
            sort(e[s].begin(),e[s].end());
        }
        int waterbye=0;
        for(int i=0;i<nsum.size();i++)
        {
            int s=nsum[i];
            int x=xig[i];
            int lowyo=lower_bound(e[s].begin(),e[s].end(),x-k+1)-e[s].begin();
            int hibye=upper_bound(e[s].begin(),e[s].end(),x)-e[s].begin();
            waterbye+=hibye-lowyo;
        }
        cout<<n*k-waterbye<<"\n";
    }
}