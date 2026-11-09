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
        int N,K;
        cin>>N>>K;
        vector<char> A(K);
        for(int i=0;i<K;i++)
        {
            cin>>A[i];
        }
        string ans(N,A[0]);
        bool solved=false;
        for(int j=0;j<K;j++)
        {
            string guess(N,A[j]);
            cout<<guess<<endl;
            string response;
            cin>>response;
            if(response=="CORRECT")
            {
                solved=true;
                break;
            }
            for(int i=0;i<N;i++)
            {
                if(response[i]!='_')
                {
                    ans[i]=response[i];
                }
            }
        }
        if(!solved)
        {
            cout<<ans<<endl;
            string response;
            cin>>response;
        }
    }
    return 0;
}