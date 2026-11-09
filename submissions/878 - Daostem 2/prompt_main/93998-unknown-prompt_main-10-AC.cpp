#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        bool q=false;
        string s;
        cin>>s;
        string sub;
        sub="write_me";
        int k=s.find(sub);
        
        if(k!=string::npos)
        {
            cout<<s<<"make_it_sound_human"<<endl;
            q=true;
        }
        sub="what_is";
        int j=s.find(sub);
        
        if(j!=string::npos)
        {
            cout<<s<<"do_not_hallucinate"<<endl;
            q=true;
        }
        
        
        sub="solve";
        int i=s.find(sub);
        
        if(i!=string::npos)
        {
            cout<<s<<"make_no_mistakes"<<endl;
            q=true;
        }
        
        if(q==false)
        {
            cout<<s<<"thank_you"<<endl;
        }
        
    }
    
    return 0;
}

