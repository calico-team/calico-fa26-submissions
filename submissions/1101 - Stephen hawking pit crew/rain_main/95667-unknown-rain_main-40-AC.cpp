#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
using namespace std;
int main(){
    long long t;
    cin >> t;
    for(long long i=0; i<t; i++){
        map<long long, vector<long long>> me;
        map<long long, vector<long long>> mn;
        vector<long long> vs;
        long long a, b;
        cin >> a >> b;
        for(long long j=0; j<a; j++){
            long long x, y, z;
            cin >> x >> y >> z;
            string s;
            cin >> s;
            long long d;
            vs.push_back(x+y);
            if(s=="E"){
                me[x+y].push_back(x);
            }else{
                mn[x+y].push_back(x);
            }
        }
        sort(vs.begin(), vs.end());
        vs.erase(unique(vs.begin(), vs.end()), vs.end());
        long long fa = 0; 
        for(long long k : vs){
            sort(me[k].begin(), me[k].end());
            sort(mn[k].begin(), mn[k].end());
            for(long long kk : me[k]){
                auto lo = lower_bound(mn[k].begin(), mn[k].end(), kk+1);
                auto hi = upper_bound(mn[k].begin(), mn[k].end(), kk+b-1);
                if(hi > lo){
                    fa += hi - lo;
                }
            }
        }
        cout << a*b-fa << endl;
    }
}