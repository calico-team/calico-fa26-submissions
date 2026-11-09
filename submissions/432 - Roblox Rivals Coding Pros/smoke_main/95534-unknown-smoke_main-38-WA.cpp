#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <string>
#include <sstream>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <numeric>
#include <iomanip>
#include <map>
using namespace std;


int main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr);
    int t; cin>>t;
    for (int id = 0;id<t;id++) {
        int n,r;
        cin>>n>>r;
        if (n<3) {
            int x;
            for (int i=0;i<n;i++) {
                cin>>x;
            }
            cout<<"YES"<<'\n';

        }
        else {
            int previous;
            pair<int,int>times = pair(0,0);
            int a;
            cin>>a;
            cin>>previous;
            times.first = r;
            times.second = r-previous+a;
            bool flag = true;
            for (int i=2;i<n;i++) {
                int x; cin>>x;
                int remaining = x-previous;
                if (times.second<=remaining) {
                    remaining -=times.second;
                    times.second = times.first;
                    times.first = r;
                    times.first-=max(0,remaining);
                    previous = x;
                }
                else {
                    if (flag) {
                        cout<<"NO"<<'\n';
                    }
                    flag = false;
                }
            }
            if (flag) {
                cout<<"YES"<<'\n';
            }
        }
    }



}