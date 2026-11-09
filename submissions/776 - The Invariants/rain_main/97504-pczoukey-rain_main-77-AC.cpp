#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while(T--)
    {
        int N;
        long long K;
        cin>>N>>K;
        const int MAXD=200001;
        vector<vector<int>> east(MAXD),north(MAXD);
        for(int i=0;i<N;i++)
        {
            int X,Y,Z;
            char D;
            cin>>X>>Y>>Z>>D;
            int diagonal=X+Y;
            if(D=='E')
            {
                east[diagonal].push_back(X);

            }
            else
            {
                north[diagonal].push_back(X);
            }
        }
        long long meetings=0;
        for(int d=0;d<MAXD;d++)
        {
            if(east[d].empty()||north[d].empty())
            {
                continue;
            }
            sort(north[d].begin(),north[d].end());
            for(int x:east[d])
            {
                long long low=x+1;
                long long high=x+K-1;
                auto left=lower_bound(north[d].begin(),north[d].end(),low);
                auto right=upper_bound(north[d].begin(),north[d].end(),high);
                meetings+=right-left;
            }
        }
        cout<<1LL*N*K-meetings<<'\n';
    }
    return 0;
}