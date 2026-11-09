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
    { //im up at 3 am to do ts contest help me
        int n,r;
        cin>>n>>r;
        int one=0;
        int two=0;
        bool ok=true;
        for(int i=0;i<n;i++)
        {
            int a;
            cin>>a;
            if(one>a)
            {
                ok=false;
            }
            else
            {
                int dundundun=a;
                if(two>dundundun)
                {
                    dundundun=two;
                }
                one=two;
                two=dundundun+r;
            }
        }
        if(ok>1) //im so cool
        {
            cout<<"YES"<<"\n";
        }
        else
        {
            cout<<"NO"<<"\n";
        }//uncle shrimb the ioi king taught us never to test code
    }
}