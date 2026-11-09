#include <bits/stdc++.h>
using namespace std;

bool solve(int n, int r, const vector<int>& a)
{
    queue<int> q;     
    int last = 0;
    for(int i=0;i<n;i++)
        {
            int t=a[i];
            while(!q.empty() && q.front()<t) q.pop();

            if(q.size()==2) return false;

            int start=q.empty()?t:last;
            last=start+r;
            q.push(last);   
        }
    return true;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        int r;
        cin >> n >> r;
        vector<int> a(n);
        for (auto& x : a) cin >> x;
        cout << (solve(n, r, a) ? "YES" : "NO") <<endl;
    }
    return 0;
}