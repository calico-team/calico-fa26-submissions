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
        int N,M,K;
        cin>>N>>M>>K;
        vector<vector<int>> children(N+1);
        queue<int> ready;
        for(int i=1;i<=N;i++)
        {
            int P;
            cin>>P;
            if(P==0)
            {
                ready.push(i);
            }
            else
            {
                children[P].push_back(i);
            }
        }
        int ans=0;
        for(int semester=0;semester<M&&!ready.empty();semester++)
        {
            int take=min(K,(int)ready.size());
            vector<int> nextSemester;
            for(int i=0;i<take;i++)
            {
                int course=ready.front();
                ready.pop();
                ans++;
                for(int child:children[course])
                {
                    nextSemester.push_back(child);
                }
            }
            for(int course:nextSemester)
            {
                ready.push(course);
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}