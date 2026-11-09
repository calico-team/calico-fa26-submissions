#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while(t--){
        int n,r; cin >> n >> r;
        vector<int> arr(100000);
        arr[0]=2;
        vector<int> points;
        for(int i = 0; i < n; i++){
            int x; cin >> x;
            arr[x]-=1;
            arr[min(x+r,(int)arr.size()-1)]+=1;
            points.push_back(x);
        }
        for(int i = 1; i < arr.size(); i++){
            arr[i]=arr[i-1]+arr[i];
        }
        bool pos = true;
        for(int i = 0; i < n; i++){
            if(arr[points[i]]<=0){
                pos = false;
            }
        }
        if(pos){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }
    }
}

