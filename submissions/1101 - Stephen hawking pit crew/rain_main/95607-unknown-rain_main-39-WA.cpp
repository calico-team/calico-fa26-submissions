#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
using namespace std;
int main(){
    int t;
    cin >> t;
    for(int i=0; i<t; i++){
        map<int, vector<int>> me;
        map<int, vector<int>> mn;
        vector<int> vs;
        int a, b;
        cin >> a >> b;
        for(int j=0; j<a; j++){
            int x, y, z;
            cin >> x >> y >> z;
            string s;
            cin >> s;
            int d;
            vs.push_back(x+y);
            if(s=="E"){
                me[x+y].push_back(x);
            }else{
                mn[x+y].push_back(x);
            }
        }
        sort(vs.begin(), vs.end());
        vs.erase(unique(vs.begin(), vs.end()), vs.end());
        int fa = 0; 
        for(int k : vs){
            sort(me[k].begin(), me[k].end());
            sort(mn[k].begin(), mn[k].end());
            for(int kk : me[k]){
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