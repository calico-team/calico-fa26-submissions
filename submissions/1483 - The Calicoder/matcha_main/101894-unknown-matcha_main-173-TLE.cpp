
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Block {
    ll x;
    int k;
};

vector<Block> decompose(ll l, ll r) {
    vector<Block> result;

    while (l <= r) {
        int k = 0;

        while (k < 30 &&
               l % (1LL << (k + 1)) == 0 &&
               l + (1LL << (k + 1)) - 1 <= r) {
            k++;
        }

        result.push_back({l, k});
        l += 1LL << k;
    }

    return result;
}

vector<Block> normalize(vector<Block> v) {
    sort(v.begin(), v.end(), [](Block a, Block b) {
        if (a.x != b.x) return a.x < b.x;
        return a.k > b.k;
    });

    vector<Block> s;

    for (auto b : v) {
        if (!s.empty() &&
            b.x < s.back().x + (1LL << s.back().k)) {
            continue;
        }

        s.push_back(b);

        while (s.size() >= 2) {
            Block b = s.back();
            Block a = s[s.size() - 2];

            if (a.k == b.k &&
                a.x + (1LL << a.k) == b.x &&
                a.x % (1LL << (a.k + 1)) == 0) {

                s.pop_back();
                s.back().k++;
            } else {
                break;
            }
        }
    }

    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<ll> L(N), R(N);

        for (int i = 0; i < N; i++)
            cin >> L[i];

        for (int i = 0; i < N; i++)
            cin >> R[i];

        vector<Block> possible = {{0, 0}};

        for (int i = 0; i < N; i++) {
            vector<Block> choices = decompose(L[i], R[i]);
            vector<Block> next;

            for (auto a : possible) {
                for (auto b : choices) {
                    int k = max(a.k, b.k);

                    ll mask = ~((1LL << k) - 1);

                    ll x = (a.x ^ b.x) & mask;

                    next.push_back({x, k});
                }
            }

            possible = normalize(move(next));
        }

        ll answer = 0;

        for (auto b : possible) {
            answer = max(answer,
                         b.x + (1LL << b.k) - 1);
        }

        cout << answer << '\n';
    }
}
