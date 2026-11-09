#include <ext/pb_ds/assoc_container.hpp>
#include <bits/stdc++.h>
#include <cstring>
 
typedef long long ll;
using namespace std;
using namespace __gnu_pbds;
 
/*template<class T> 
using Tree=tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;*/

vector<int> bucket[200001][2];

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt--){
        ll n,k; cin >> n >> k;
        for (int i=0; i<n; i++){
            int t1,t2,t3; char t4; cin >> t1 >> t2 >> t3 >> t4;
            bucket[t1+t2][(t4=='N')].push_back(t1);
        }
        for (int i=0; i<=200000; i++){
            sort(bucket[i][0].begin(),bucket[i][0].end());
            sort(bucket[i][1].begin(),bucket[i][1].end());
        }
        ll out=0;
        for (int i=0; i<=20; i++){
            queue<int> in;
            int id=0;
            for (int j: bucket[i][0]){
                while (id<int(bucket[i][1].size()) && bucket[i][1][id]<j+k){
                    in.push(bucket[i][1][id]);
                    id++;
                }
                while (!in.empty() && in.back()<j){
                    in.pop();
                }
                out+=int(in.size());
            }
            bucket[i][0].clear(); bucket[i][1].clear();
        }
        cout << n*k-out << "\n";
    }
}