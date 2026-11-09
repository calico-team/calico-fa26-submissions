#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<iterator>
#include<string>
#include<sstream>
#include<queue>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<numeric>
#include<iomanip>
#include<map>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(nullptr);
    int t;cin>>t;
    for (int id=0;id<t;id++) {
        int n,m,q;
        cin>>n>>m>>q;
        vector<vector<int>>grid(n,vector<int>(m,0));
        for (int iq=0;iq<q;iq++) {
            int r,c,p;
            cin>>r>>c>>p;
            for (int i = r-p;i<r+p+1;i++) {
                for (int j = c-p;j<c+p+1;j++) {
                    int x = p*p-(i-r)*(i-r)-(j-c)*(j-c)+1;
                    if (x>0) {
                        grid[i][j] = x;
                    }
                }
            }
        }
        for (int i=0;i<n;i++) {
            for (int j=0;j<m;j++) {
                cout<<grid[i][j]<< " \n"[j==m-1];

            }

        }
    }
}