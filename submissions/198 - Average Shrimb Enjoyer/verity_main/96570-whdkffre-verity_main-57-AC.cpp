#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; //im never touching info again
    cin>>t;
    while(t--)
    {
        int n,k;
        cin>>n>>k;
        vector<char>l(k);
        for(int i=0;i<k;i++)
        {
            cin>>l[i];
        }
        string rightthere(n,'_');
        int place=0;
        while(true)
        {
            string idk=rightthere;
            for(int i=0;i<n;i++)
            {
                if(idk[i]=='_')
                {
                    idk[i]=l[place];
                }
            }
            cout<<idk<<endl;
            string radda;
            cin>>radda;
            if(radda=="CORRECT")
            {
                break;
            }
            for(int i=0;i<n;i++)
            {
                if(radda[i]!='_')
                {
                    rightthere[i]=radda[i];
                }
            }
            if(place+1<k)
            {
                place++;
            }
        }// calico this aint over
    }
}