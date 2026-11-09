#include<bits/stdc++.h>
using namespace std;
#define int long long
#define a2 array<int,2>
#define a3 array<int,3>
struct trie{
    struct node{
        a2 ch={0,0};
        int cnt=0;
    };
    vector<node> tr{1};
    int get(){
        tr.emplace_back();
        return tr.size()-1;
    }
    void add(int x){
        int now=0;
        tr[now].cnt++;
        for(int i=29;i>=0;i--){
            int b=(x>>i)&1;
            if(!tr[now].ch[b]) tr[now].ch[b]=get();
            now=tr[now].ch[b];
            tr[now].cnt++;
        }
    }
    void out(int x){
        int p[30],id[30];
        int b[30];
        int now=0;
        tr[now].cnt--;
        for(int d=0,i=29;i>=0;i--,d++){
            b[d]=(x>>i)&1;
            p[d]=now;
            now=tr[now].ch[b[d]];
            id[d]=now;
            tr[now].cnt--;
        }
        for(int d=29;d>=0;d--){
            if(tr[id[d]].cnt==0){
                tr[p[d]].ch[b[d]]=0;
                tr[id[d]]=node{};
            }
        }
    }
    int mx(int x){
        int now=0,ans=0;
        for(int i=29;i>=0;i--){
            int b=(x>>i)&1;
            int v=tr[now].ch[b^1];
            if(v && tr[v].cnt>0){
                ans|=1ll<<i;
                now=v;
            }
            else now=tr[now].ch[b];
        }
        return ans;
    }
};
void solve(){
    int n;
    cin>>n;
    vector<int> a(n),v(n);
    for(int& x:a){
        cin>>x;
        x--;
    }
    for(int& x:v){
        cin>>x;
    }
    vector<int> deg(n);
    for(int i=0;i<n;i++){
        deg[a[i]]++;
    }
    queue<int> q;
    vector<bool> out(n),in(n),vis(n);
    for(int i=0;i<n;i++){
        if(!deg[i]){
            q.push(i);
        }
    }
    while(q.size()){
        int i=q.front();
        q.pop();
        out[i]=1;
        if(--deg[a[i]]==0){
            q.push(a[i]);
        }
    }
    vector<vector<int>> rv(n);
    for(int i=0;i<n;i++){
        if(!out[i]){
            in[i]=1;
        }
        else{
            rv[a[i]].push_back(i);
        }
    }
    vector<int> ans(n);
    for(int i=0;i<n;i++){
        if(!in[i] || vis[i]) continue;
        vector<int> c;
        int _=i;
        do{
            c.push_back(_);
            vis[_]=1;
            _=a[_];
        }while(_!=i);
        int sz=c.size();
        vector<int> pre(3*sz+1);
        for(int j=1;j<=3*sz;j++){
            pre[j]=pre[j-1]^v[c[(j-1)%sz]];
        }
        trie tr;
        for(int j=1;j<=2*sz;j++){
            tr.add(pre[j]);
        }
        for(int k=0;k<sz;k++){
            ans[c[k]]=tr.mx(pre[k]);
            vector<a3> stk;
            for(int x:rv[c[k]]){
                stk.push_back({x,pre[k],0});
            }
            while(stk.size()){
                auto [i,x,out]=stk.back();
                stk.pop_back();
                if(out){
                    tr.out(x);
                    continue;
                }
                int nxt=x^v[i];
                tr.add(x);
                ans[i]=tr.mx(nxt);
                stk.push_back({i,x,1});
                for(int x:rv[i]){
                    stk.push_back({x,nxt,0});
                }
            }
            if(k+1<sz){
                tr.out(pre[k+1]);
                tr.add(pre[k+2*sz+1]);
            }
        }
    }
    for(int x:ans){
        cout<<x<<' ';
    }
    cout<<"\n";
}
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--){
        solve();
    }
    return 0;
}