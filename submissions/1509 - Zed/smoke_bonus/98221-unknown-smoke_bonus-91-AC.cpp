#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int tc;
    if (!(cin >> tc))
        return 0;

    while (tc--)
    {
        int n;
        long long r;
        vector<long long> a;
        cin >> n >> r;

        for (int i = 0; i < n; i++)
        {
            long long a_i;
            cin >> a_i;
            a.push_back(a_i);
        }

        bool flag = true;
        queue<long long> q;
        q.push(0);
        q.push(0);

        for (int i = 0; i < n; i++)
        {
            long long earliest_ready = q.front();

            if (earliest_ready > a[i])
            {
                cout << "NO";
                flag = false;
                break;
            }

            q.pop();
            long long second_ready = q.front();
            long long new_ready = max(a[i], second_ready) + r;
            q.push(new_ready);
        }

        if (flag)
            cout << "YES";
        cout << "\n";
    }
    return 0;
}