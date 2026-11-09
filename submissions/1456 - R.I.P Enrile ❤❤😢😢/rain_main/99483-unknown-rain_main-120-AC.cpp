// Nov 09 2026, 09:24

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fastIO cin.tie(NULL); ios::sync_with_stdio(NULL)
#define fi first
#define se second

// find the first index i where x <= arr[i]
int le(int x, vector<int> &arr) {
    int l = -1, r = arr.size();
    while(l + 1 < r) {
        int m = (l + r) / 2;
        if(x <= arr[m]) r = m;
        else l = m;
    }

    return r;
}



// find the last index i where arr[i] <= x
int ge(int x, vector<int> &arr) {
    int l = -1, r = arr.size();
    while(l + 1 < r) {
        int m = (l + r) / 2;
        if(arr[m] <= x) l = m;
        else r = m;
    }

    return l;
}

int main() {
    fastIO;

    int T; cin >> T;
    while(T--) {
        ll n, k; cin >> n >> k;
        map<int, vector<int>> ns, es;
        set<tuple<int, int, char>> fah;
        for(int i = 0; i < n; i++) {
            int x, y, z; char c; cin >> x >> y >> z >> c;

            if(c == 'N') ns[x + y].push_back(x);
            else es[x + y].push_back(x);
        }

        for(auto &[j, i] : ns) sort(i.begin(), i.end()); 
        for(auto &[j, i] : es) sort(i.begin(), i.end()); 

        ll tot = n * k;
        ll fuck = 0;
        
        // cerr << endl << endl;
        for(auto [diag, arr] : es) {
            // cerr << "new " << diag << endl;
            // for(auto i : ns[diag]) cerr << i << ' ';
            // cerr << endl;
            for(auto i : arr) {
                int a = le(i, ns[diag]);
                int b = ge(i + k - 1, ns[diag]);
                // cerr << i << ' ' << i + k - 1 << ' ' << a << ' ' << b << ' ' << max(b - a + 1, 0) << endl;
                fuck += max(b - a + 1, 0);
            }            
        }

        cout << tot - fuck << '\n';
    }

    return 0;
}