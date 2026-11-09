#include<bits/stdc++.h>
using namespace std;
vector<array<int,2> > tree;
void add(int &root,int x){
    if(root==0){
        root=tree.size();
        tree.push_back({0,0});
    }
    int u=root;
    for(int i=29;i>=0;i--){
        int b=(x>>i)&1;
        if(tree[u][b]==0){
            int next=tree.size();
            tree.push_back({0,0});
            tree[u][b]=next;
        }
        u=tree[u][b];
    }
}

int insert(int root,int x){
    int result=tree.size();
    array<int,2> temp=tree[root];
    tree.push_back(temp);

    int u=result;
    int v=root;
    for(int i=29;i>=0;i--){
        int b=(x>>i)&1;
        int next=tree[v][b];
        temp=tree[next];
        int now=tree.size();
        tree.push_back(temp);

        tree[u][b]=now;
        u=now;
        v=next;
    }
    return result;
}
int query(int root,int x){
    int result=0;
    int u=root;
    for(int i=29;i>=0;i--){
        int b=(x>>i)&1;
        if(tree[u][b^1]!=0){
            result|=(1<<i);
            u=tree[u][b^1];
        }else{
            u=tree[u][b];
        }
    }
    return result;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie();
    cout.tie(); 
    int T;
    cin>>T;
    for(int i=0;i<T;i++){
        int N;
        cin>>N;
        vector<int> A(N+1),V(N+1),degree(N+1);
        for(int j=1;j<=N;j++){
            cin>>A[j];
            degree[A[j]]++;
        }
        for(int j=1;j<=N;j++){
            cin>>V[j];
        }
        queue<int> q;
        vector<int> order;
        for(int j=1;j<=N;j++){
            if(degree[j]==0){
                q.push(j);
            }
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            order.push_back(u);

            degree[A[u]]--;
            if(degree[A[u]]==0){
                q.push(A[u]);
            }
        }
        tree.clear();
        tree.reserve(62LL*N+1);
        tree.push_back({0,0});
        vector<int> p(N+1),root(N+1),answer(N+1);
        vector<int> visited(N+1);
        for(int j=1;j<=N;j++){
            if(degree[j]==0||visited[j]){
                continue;
            }
            vector<int> cycle;
            int u=j;
            int sum=0;
            while(!visited[u]){
                visited[u]=1;
                cycle.push_back(u);
                p[u]=sum;
                sum^=V[u];
                u=A[u];
            }
            int r=0;
            for(int k=0;k<(int)cycle.size();k++){
                int x=cycle[k];
                add(r,p[x]);
                if(sum!=0){
                    add(r,p[x]^sum);
                }
            }
            for(int k=0;k<(int)cycle.size();k++){
                int x=cycle[k];
                root[x]=r;
                answer[x]=query(r,p[x]);
            }
        }
        for(int j=(int)order.size()-1;j>=0;j--){
            int u=order[j];
            int next=A[u];
            p[u]=V[u]^p[next];
            root[u]=insert(root[next],p[next]);
            answer[u]=query(root[u],p[u]);
        }
        for(int j=1;j<=N;j++){
            if(j>1){
                cout<<" ";
            }
            cout<<answer[j];
        }
        cout<<'\n';
    }
    return 0;
}
