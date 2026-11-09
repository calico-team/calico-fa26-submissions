#include <bits/stdc++.h>
using namespace std;
int win=-99;
int lose=-100;
vector<vector<int>> is_win;
void solve(){
    int n;
    cin>>n;
    int m;
    cin>>m;
    int k;
    cin>>k;
    vector<int> prerequisite_reference;
    vector<vector<int>> build_off;
    // vector<bool> is_prerequisite;
    for(int i=0; i<n; i+=1){
        build_off.push_back({});
    }
    set<int> has_been_learned;
    set<int> is_learnable;
    for(int i=0; i<n; i+=1){
        int asdfasdfasdf;
        cin>>asdfasdfasdf;
        asdfasdfasdf-=1;
        // is_prerequisite[asdfasdfasdf]=true;
        // prerequisite_reference.push_back(asdfasdfasdf);
        if(asdfasdfasdf>-1){
            build_off[asdfasdfasdf].push_back(i);
        }
        if(asdfasdfasdf==-1){
            is_learnable.insert(i);
        }
    }
    int max_level_reached=0;
    int current_level_filledness=0;
    int ans=0;

    vector<int> to_be_added;
    while(max_level_reached<m){
        // cout<<max_level_reached<<" AAA "<<is_learnable.size()<<" WHY\n";
        int aaaaaaaaaa=*is_learnable.begin();
        // cout<<aaaaaaaaaa<<" current\n";
        for(int i=0; i<build_off[aaaaaaaaaa].size(); i+=1){
            to_be_added.push_back(build_off[aaaaaaaaaa][i]);
            // cout<<build_off[aaaaaaaaaa][i]<<" this was added to next_learnable\n";
        }
        is_learnable.erase(aaaaaaaaaa);
        ans+=1;
        current_level_filledness+=1;
        if(current_level_filledness==k or is_learnable.size()==0){
            max_level_reached+=1;
            for(int i=0; i<to_be_added.size(); i+=1){
                is_learnable.insert(to_be_added[i]);
            }
            current_level_filledness=0;
            to_be_added.clear();
        }
    }
    cout<<ans<<"\n";
}
int main(){
    int t;
    cin>>t;
    for(int test=0; test<t; test+=1){
        solve();
    }
}   