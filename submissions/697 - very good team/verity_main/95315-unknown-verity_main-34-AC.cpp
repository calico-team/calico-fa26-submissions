#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr int maxN = 1e6 + 1;
int N, K, T;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;

    for (int z = 0; z < T; z++)
    {
        vector<char> letters;
        cin >> N >> K;
        bool already = false;
        char where[N];
        for (int i = 0; i < K; i++)
        {
            char n; cin >> n;
            letters.push_back(n);
        }
        for (int i = 0; i < K && !already; i++)
        {
            string res(N, letters[i]);
            cout << res << endl;
            string respond; cin >> respond;
            if (respond == "CORRECT") { already = true; break; }
            for (int j = 0; j < N; j++)
            {
                if (respond[j] != '_') where[j] = letters[i];
            }
        }
        if (!already)
        {
            for (int i = 0; i < N; i++)
            {
                cout << where[i];
            }
            cout << endl;
            string res;
            cin >> res;
        }
    }
}