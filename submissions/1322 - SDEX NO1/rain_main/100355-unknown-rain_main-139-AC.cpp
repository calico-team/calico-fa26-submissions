#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);         

    int t;
    cin >> t;

    while(t--){
        int n;
        long long k;
        cin >> n >> k;
        vector<pair<long long, long long>> East, North;

        for(int i = 0; i < n; i++){
            long long x,y,z;
            char d;
            cin >> x >> y >> z >> d;

            if(d == 'E'){
                East.push_back({x+y,x});
            }
            else{
                North.push_back({x+y,x});
            }
        }

        sort(North.begin(), North.end());
        long long ans = n*k;

        for(int i = 0; i < East.size();i++){
            long long xysum = East[i].first;
            long long x = East[i].second;
            int left = lower_bound(North.begin(), North.end(), make_pair(xysum, x+1))- North.begin();
            int right = lower_bound(North.begin(), North.end(), make_pair(xysum, x+k))- North.begin();
            ans -= right - left;

        }
        cout << ans << "\n";
    }

    return 0;
}

