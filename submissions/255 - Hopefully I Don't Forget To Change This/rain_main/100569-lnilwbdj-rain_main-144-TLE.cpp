#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin >> t;
    while(t--){
        int n,k;
        cin >> n >> k;
        vector<int> x(n),y(n),z(n);
        vector<char> d(n);
        for(int i=0;i<n;i++) cin >> x[i] >> y[i] >> z[i] >> d[i];
        int total = 0;
        for(int ni=0;ni<k;ni++){
            set<pair<int,int>> col;
            for(int i=0;i<n;i++) col.insert(make_pair(x[i],y[i]));
            total += col.size();
            for(int i=0;i<n;i++){
                if(d[i]=='E') x[i]++;
                else y[i]++;
            }
        }
        cout << total << endl;
    }
}
