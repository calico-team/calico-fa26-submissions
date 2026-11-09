#include <bits/stdc++.h>
using namespace std;
int main(){
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    int T;
    cin>>T;
    while(T--){
        long long n,k;
        cin>>n>>k;

        map<long long,vector<long long>> este, norte;
        for(int i=0; i< n; i++){
            long long x,y,z;
            char d;
            cin>>x>>y>>z>>d;
            if(d=='E') este[x+y].push_back(x);
            else norte[x+y].push_back(x);
        }
        long long cruces=0;
        for(auto&[s, listae]:este){
            auto it=norte.find(s);
            if(it==norte.end()) continue;

            vector<long long>& listan= it->second;
            sort(listan.begin(), listan.end());
            for(long long xi: listae){
                auto abajo= lower_bound(listan.begin(), listan.end(), xi+1);
                auto arriba = upper_bound(listan.begin(), listan.end(), xi+k-1);
                cruces+= arriba - abajo;
            }
        
        }
        cout<< n*k-cruces<<"\n";
    }
    return 0;
}
    