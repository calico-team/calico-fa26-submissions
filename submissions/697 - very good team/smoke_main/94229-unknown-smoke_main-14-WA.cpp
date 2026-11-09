#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr int maxN = 1e6 + 1;
int N, R, T;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;

    for (int z = 0; z < T; z++)
    {
        int charges = 2;
        cin >> N >> R;
        int prev = 0;
        bool result = true;
        for (int i = 0; i < N; i++)
        {
            int n; cin >> n;
            charges = min(2, charges + (n - prev) / R);
            if (charges != 0) charges--;
            else result = false;
            prev = n;
        }
        cout << (result ? "YES" : "NO") << "\n";
    }
}