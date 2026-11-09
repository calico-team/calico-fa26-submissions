#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

vector<set<int>> v;
vector<int> p;

bool comp(int a, int b){
    return v[a].size()>v[b].size();
}

int main(){
    int tests;
    cin>>tests;
    for(int test=0;test<tests;test++){
        int n, m, k;
        cin>>n>>m>>k;
        v=vector<set<int>>(n);
        p=vector<int>(n,-1);
        set<int> ready;
        
        for(int i=0;i<n;i++){
            int a;
            cin>>a;
            if(a>0){
                v[a-1].insert(i);
                p[i]=a-1;
            }
        }
        for(int i=0;i<n;i++)
            if(p[i]==-1)
                ready.insert(i);

        int ct=0;
        for(int i=0;i<m;i++){
            vector<int> able(0);
            for(int j:ready)
                able.push_back(j);
            sort(able.begin(),able.end(),comp);
            int x=able.size();
            for(int j=0;j<k;j++){
                if(j>=x) break;
                ct++;
                for(int z:v[able[j]])
                    ready.insert(z);
                ready.erase(able[j]);
            }
        }
        cout<<ct<<endl;
    }
    return 0;
}
