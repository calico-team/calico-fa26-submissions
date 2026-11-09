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
        long long R;
        cin>>N>>R;
        deque<long long> recharge;
        int charges=2;
        bool possible=true;
        for(int i=0;i<N;i++)
        {
            long long A;
            cin>>A;
            while(!recharge.empty()&&recharge.front()<=A)
            {
                charges++;
                recharge.pop_front();
            }
            if(charges==0)
            {
                possible=false;
            }
            else
            {
                charges--;
                long long finish;
                if(recharge.empty())
                {
                    finish=A+R;
                }
                else
                {
                    finish=recharge.back()+R;
                }
                recharge.push_back(finish);
            }

        }
        cout<<(possible?"YES":"NO")<<'\n';
    }
    return 0;
}