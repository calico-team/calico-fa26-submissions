#include<iostream>
#include<vector>
#include<set>
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
        int ct=0;
        for(int i=0;i<m;i++){
            vector<int> able(0);
            int minimum=n, minidx=-1;
            for(int j:ready)
                able.push_back(j);
            sort(able.begin(),able.end(),comp);
            for(int j=0;j<k;j++){
                if(j>=able.size()) break;
                v[able[j]].erase(able[j]);
                ct++;
                if(v[able[j]].size()==0)
                    ready.insert(p[able[j]]);
                ready.erase(able[j]);
                p[able[j]]=-1;
            }
        }
        cout<<ct<<endl;
    }
    return 0;
}