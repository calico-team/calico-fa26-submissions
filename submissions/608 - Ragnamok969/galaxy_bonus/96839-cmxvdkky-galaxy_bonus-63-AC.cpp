#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector <vector <char>> adj;
vector <ll> par;
ll find (ll a){
    if (a == par[a]) return a;
    return par[a] = find(par[a]);
}
void merge(ll x, ll y){
    x = find(x); y = find(y);
    if (x != y) par[y] = x;
}
int main(){
    ll t; cin >> t;
    while (t--){
        ll a, b, c; cin >> a >> b >> c;
        adj.assign(a + 1, vector <char> (b + 1));
        par.resize((2 * a * b));
        iota(par.begin(), par.end(), 0);
        for (int i = 1; i <= a; i++){
            for (int j = 1; j <= b; j++) cin >> adj[i][j];
        }
        for (int i = 1; i <= a; i++){
            for (int j = 1; j <= b; j++){
                for (int k = 0; k < 2; k++){
                    bool checker = false;
                    if (adj[i][j] == '.') checker = true;
                    else if (adj[i][j] == 'B' && k == 0) checker = true;
                    else if (adj[i][j] == 'R' && k == 1) checker = true;
                    if (!checker) continue;
                    ll koor1 = ((i - 1) * b + (j - 1)) * 2 + k;
                    if (j < b){
                        bool checker2 = false;
                        if (adj[i][j + 1] == '.') checker2 = true;
                        else if (adj[i][j + 1] == 'B' && k == 0) checker2 = true;
                        else if (adj[i][j + 1] == 'R' && k == 1) checker2 = true;
                        if (checker2){
                            ll koor2 = ((i - 1) * b + j) * 2 + k;
                            merge(koor1, koor2);
                        }
                    }
                    if (i < a){
                        bool checker2 = false;
                        if (adj[i + 1][j] == '.') checker2 = true;
                        else if (adj[i + 1][j] == 'B' && k == 0) checker2 = true;
                        else if (adj[i + 1][j] == 'R' && k == 1) checker2 = true;
                        if (checker2){
                            ll koor2 = (i * b + (j - 1)) * 2 + k;
                            merge(koor1, koor2);
                        }
                    }
                }
                if (adj[i][j] == '.'){
                    ll bl = ((i - 1) * b + (j - 1)) * 2;
                    ll rd = bl + 1;
                    merge(bl, rd);
                }
            }
        }
        for (int i = 0; i < c; i++){
            ll x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            x1++; y1++; x2++; y2++;
            ll st = ((x1 - 1) * b + (y1 - 1)) * 2;
            ll fb = ((x2 - 1) * b + (y2 - 1)) * 2;
            ll fr = fb + 1;
            st = find(st); fb = find(fb); fr = find(fr);
            if (st == fb || st == fr) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }
}