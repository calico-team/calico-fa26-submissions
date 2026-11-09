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
        vector<int> parent(N+1),remaining(N+1);
        vector<int> height(N+1,1);
        queue<int> leaves;
        vector<int> roots;
        for(int i=1;i<=N;i++)
        {
            cin>>parent[i];
            if(parent[i]==0)
            {
                roots.push_back(i);
            }
            else
            {
                children[parent[i]].push_back(i);
                remaining[parent[i]]++;
            }
        }
        for(int i=1;i<=N;i++)
        {
            if(remaining[i]==0)
            {
                leaves.push(i);
            }
        }
        while(!leaves.empty())
        {
            int u=leaves.front();
            leaves.pop();
            int p=parent[u];
            if(p!=0)
            {
                height[p]=max(height[p],height[u]+1);
                remaining[p]--;
                if(remaining[p]==0)
                {
                    leaves.push(p);
                }
            }
        }
        priority_queue<pair<int,int>> ready;
        for(int root:roots)
        {
            ready.push({height[root],root});

        }
        int ans=0;
        for(int semester=1;semester<=M&&!ready.empty();semester++)
        {
            int take=min(K,(int)ready.size());
            vector<int> completed;
            for(int i=0;i<take;i++)
            {
                int course=ready.top().second;
                ready.pop();
                ans++;
                completed.push_back(course);

            }
            for(int course:completed)
            {
                for(int child:children[course])
                {
                    ready.push({height[child],child});
                }
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}