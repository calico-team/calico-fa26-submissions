// Shortcuts:
// Ctrl+Shift+B  -> Build & Run
// Ctrl+Shift+R  -> Reset Workspace (new problem)
// Ctrl+Alt+L    -> 3-pane layout (main.cpp | input.txt | output.txt)

#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
    int n,r;
    cin>>n>>r;

    vector<int> nums(n);
    for(int i=0;i<n;i++){
        cin>>nums[i];
    }

    for(int i=2;i<n;i++){
        if(nums[i]-nums[i-1]<r){
            cout<<"NO"<<endl;
            return;
        }
    }
    
    cout<<"YES"<<endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    cin >> t; 

    while (t--) {
        solve();
    }

    return 0;
}
