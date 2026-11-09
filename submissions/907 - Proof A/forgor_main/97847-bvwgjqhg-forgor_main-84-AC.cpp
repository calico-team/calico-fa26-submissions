#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll MOD = 411947;
// const ll MOD = 11;
const int max_n = 2 * 1e5;

vector<int> neighbors[max_n];
int parents[max_n];

void dfs(int node, int parent) {
    parents[node] = parent;
    for (int n : neighbors[node]) {
        if (n == parent) {
            continue;
        }
        dfs(n, node);
    }
}

vector<int> bits(ll a) {
    vector<int> out;
    while (a > 0) {
        out.push_back(a%2);
        a >>= 1;
    }
    return out;
}

ll inverse(ll a) {
    ll pow = MOD-2;

    vector<int> b = bits(pow);

    ll inv = a;
    for (int i = b.size()-2; i >= 0; i--) {
        inv = inv * inv;
        inv %= MOD;
        if (b[i] == 1) {
            inv *= a;
        }
        inv %= MOD;
    }

    return inv;
}


int main() {
    string phase;
    cin >> phase;
    if (phase == "FIRST") {
        int n;
        cin >> n;

        for (int i = 0; i < (n-1); i++) {
            int a, b;
            cin >> a >> b;
            a--;
            b--;
            neighbors[a].push_back(b);
            neighbors[b].push_back(a);
        }

        dfs(0, -1);
        ll as[n];
        ll checksum = 0;
        for (int i = 0; i < (n-1); i++) {
            as[i] = parents[i+1];
            checksum += (i + 1) * as[i];
            checksum %= MOD;
        }
        as[n-1] = checksum;

        for (int i = 0; i < (n-1); i++) {
            cout << as[i] << " ";
        }
        cout << as[n-1] << endl;
    } else {
        int n;
        cin >> n;

        ll as[n];
        int sus = -1;
        for (int i = 0; i < n; i++) {
            cin >> as[i];
            if (as[i] == -1) {
                sus = i;
            }
        }

        if (sus != (n-1)) {
            ll new_cs = 0;
            for (int i = 0; i < (n-1); i++) {
                if (i != sus) {
                    new_cs += (i+1) * as[i];
                    new_cs %= MOD;
                }
            }

            // new_cs + (sus+1) * a = as[n-1]
            
            as[sus] = ((as[n-1] - new_cs)%MOD) * (inverse(sus+1)%MOD) % MOD;
            as[sus] += MOD;
            as[sus] %= MOD;
            
        }

        for (int i = 0; i < (n-1); i++) {
            cout << (i+2) << " " << 1+as[i] << endl;
        }




    }

}
