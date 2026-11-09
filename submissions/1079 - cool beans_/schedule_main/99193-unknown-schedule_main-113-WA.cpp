#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

vector<set<int>> v;
vector<int> p;

bool comp(int a, int b){
    return v[p[a]].size()<v[p[b]].size();
}

int main(){
    int tests;
    cin>>tests;
    for(int test=0;test<tests;test++){
        int n, m, k;
        cin>>n>>m>>k;
        v=vector<set<int>>(n);
        p=vector<int>(n);
        set<int> ready;
        
        for(int i=0;i<n;i++){
            int a;
            cin>>a;
            if(a>0) v[a-1].insert(i);
            p[i]=a-1;
        }
        
        for(int i=0;i<n;i++)
            if(v[i].size()==0)
                ready.insert(i);
        cout<<"READY: ";
        for(int i:ready)
            cout<<i<<", ";
        cout<<endl<<endl;
        int ct=0;
        
        for(int i=0;i<m;i++){
            cout<<"----------------"<<endl;
            cout<<"semester "<<i+1<<endl;
            vector<int> able(0);
            for(int j:ready)
                able.push_back(j);
            sort(able.begin(),able.end(),comp);
            cout<<"ABLE: ";
            for(int j=0;j<able.size();j++)
                cout<<able[j]<<". ";
            cout<<endl;
            int x=able.size();
            for(int j=0;j<k;j++){
                if(j>=x) break;
                v[able[j]].erase(able[j]);
                ct++;
                if(v[able[j]].size()==0)
                    ready.insert(p[able[j]]);
                ready.erase(able[j]);
                p[able[j]]=-1;
            }
            cout<<"P: ";
            for(int j=0;j<p.size();j++){
                cout<<p[i]<<" ";
            }cout<<endl;
            cout<<"V: "<<endl;
            for(int j=0;j<n;j++){
                cout<<j<<"; ";
                for(int z:v[j])
                    cout<<z<<", ";
                cout<<endl;
            }
            cout<<endl;
            cout<<"READY: ";
            for(int j:ready)
                cout<<j<<", ";
            cout<<endl<<endl;
            cout<<endl;
            cout<<"---------------------"<<endl;
        }
        cout<<ct<<endl;
    }
    return 0;
}
