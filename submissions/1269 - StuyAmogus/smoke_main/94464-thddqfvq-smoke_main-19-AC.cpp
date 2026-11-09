#include <bits/stdc++.h>
using namespace std;

void solve(vector<int>& v, int r){
    bool good = true;
    pair<int,int> charged_times = {1,1};
    for (int i = 0; i < v.size() && good; i++){
        if (charged_times.first <= v[i]){
            charged_times.first = max(v[i],charged_times.second) + r;
        }
        else if (charged_times.second <= v[i]){
            charged_times.second = max(v[i],charged_times.first) + r;
        }
        else{
            good = false;
        }
    }
    if (good){
        cout << "YES\n";
    }else{
        cout << "NO\n";
    }
}

int main() {
	int T;
    cin >> T;
    for (int i = 0; i < T; i++){
        int n, r;
        cin >> n >> r;
        vector<int> v(n);
        for (int &j : v) cin >> j;
        solve(v, r);
    }
}
