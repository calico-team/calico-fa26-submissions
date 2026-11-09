// Nov 09 2026, 10:07

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fastIO cin.tie(NULL); ios::sync_with_stdio(NULL)
#define fi first
#define se second
#define cerr if(0) cout

struct Earfquake{
    ll r, c, power;

    Earfquake(): r(0), c(0), power(0) {};
    Earfquake(ll a, ll b, ll x): r(a), c(b), power(x) {};

    void swa() {
        swap(r, c);
    }
};

vector<vector<ll>> solve(int n, int m, vector<Earfquake> events) {
    vector<vector<vector<tuple<ll, ll, ll>>>> constant, linear, quadratic;
    // update, val, event id
    constant = linear = quadratic = vector<vector<vector<tuple<ll, ll, ll>>>>(n, vector<vector<tuple<ll, ll, ll>>>(m + 1));
    
    for(int index = 0; index < events.size(); index++) {
        Earfquake i = events[index];
        cerr << i.c << ' ' << i.r << ' ' << i.power << endl;
        for(ll j = 0; j < n; j++) {
            if((j - i.r) * (j - i.r) > i.power * i.power) continue;

            long double X = sqrtl(i.power * i.power - (j - i.r) * (j - i.r));
            ll l = ceil(i.c - X);
            ll r = floor(i.c + X);
            cerr << j << ' ' << l << ' ' << r << endl;

            ll con = (i.power * i.power) - (j - i.r) * (j - i.r) - i.c * i.c + 1;
            ll lin = (2 * i.c);

            constant[j][l].emplace_back(1, con, index);
            constant[j][r + 1].emplace_back(-1, con, index);

            linear[j][l].emplace_back(1, lin, index);
            linear[j][r + 1].emplace_back(-1, lin, index);

            quadratic[j][l].emplace_back(1, -1, index);
            quadratic[j][r + 1].emplace_back(-1, -1, index);
        } cerr << endl;
    }
    
    vector<vector<ll>> grid(n, vector<ll>(m, 0));
    for(ll i = 0; i < n; i++) {
        set<pair<ll, ll>> updatesC;
        set<pair<ll, ll>> updatesL;
        set<pair<ll, ll>> updatesQ;

        for(ll j = 0; j < m; j++) {
            for(auto &[x, y, z] : constant[i][j]) {
                if(x == 1) updatesC.emplace(z, y);
                else updatesC.erase({z, y});
            }

            for(auto &[x, y, z] : linear[i][j]) {
                if(x == 1) updatesL.emplace(z, y);
                else updatesL.erase({z, y});
            }

            for(auto &[x, y, z] : quadratic[i][j]) {
                if(x == 1) updatesQ.emplace(z, y);
                else updatesQ.erase({z, y});
            }

            if(updatesC.size() == 0) continue;

            grid[i][j] = ((*updatesC.rbegin()).second) + ((*updatesL.rbegin()).second) * j + ((*updatesQ.rbegin()).second) * j * j;
        }
    }

    return grid;
}

int main() {
    fastIO;

    int T; cin >> T;
    while(T--) {
        int n, m, k; cin >> n >> m >> k;
        vector<Earfquake> events(k);
        
        for(int i = 0; i < k; i++) {
            int a, b, c; cin >> a >> b >> c; a--, b--;
            events.emplace_back(a, b, c);
        }

        bool flip = n > m;
        if(flip) {
            swap(n, m);
            for(auto &i : events) i.swa();
        }

        vector<vector<ll>> ans = solve(n, m, events);

        if(flip) {
            swap(n, m);
            vector<vector<ll>> sub(n, vector<ll>(m, -1));
            for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                sub[i][j] = ans[j][i];
            
            ans = sub; // on toogie replace
        }

        for(auto i : ans) {
            for(auto j : i) cout << j << ' ';
            cout << '\n';
        }
    }

    return 0;
}