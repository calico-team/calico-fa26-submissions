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
    {
        string s;
        cin>>s;
        string a="write_me";
        string b="what_is";
        string c="solve";
        int abig=a.size();
        int bbig=b.size();
        int cbig=c.size();
        bool athere=false;
        bool bthere=false;
        bool cthere=false;
        for(int i=0;i<s.size();i++)
        {
            bool ok=true;
            for(int j=0;j<la;j++)
            {
                if(s[i+j]!=a[j])
                {
                    ok=false;
                    break;
                }
            }
            if(ok==1)
            {
                athere=true;
            }
        }
        for(int i=0;i<n;i++)
        {
            bool ok=true;
            for(int j=0;j<lb;j++)
            {
                if(s[i+j]!=b[j])
                {
                    ok=false;
                    break;
                }
            }
            if(ok)
            {
                bthere=true;
            }
        }
        for(int i=0;i<n;i++)
        {
            bool ok=true;
            for(int j=0;j<lc;j++)
            {
                if(s[i+j]!=c[j])
                {
                    ok=false;
                    break;
                }
            }
            if(ok==true)
            {
                cthere=true;
            }
        }
        if(athere)
        {
            cout<<s<<"make_it_sound_human";
        }
        else if(bthere)
        {
            cout<<s<<"do_not_hallucinate";
        }
        else if(cthere)
        {
            cout<<s<<"make_no_mistakes";
        }
        else
        {
            cout<<s<<"thank_you"
        }
    }
}