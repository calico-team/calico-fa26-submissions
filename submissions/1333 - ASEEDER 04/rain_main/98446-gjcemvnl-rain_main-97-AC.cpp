#include <bits/stdc++.h>
#include <tuple>
using namespace std;
/*
* Return an integer denoting the amount of rain collected after the Kth nights
* 
* N: Number of drones
* K: Number of nights
* L: a list in this order [X, Y, Z, D] for each drone
*   X: Starting X location of Drone
*   Y: Starting Y location of Drone
*   Z: Starting Z location of Drone
*   D: Starting direction of Drone
*/
long long solve(int N, int K, vector<tuple<int, int, int, char>> L)
{
    unordered_map<int, vector<pair<int, char>>> groups;
    for (int i = 0; i < N; i++)
    {
        int x = get<0>(L[i]);
        int y = get<1>(L[i]);
        char d = get<3>(L[i]);
        groups[x + y].push_back({x, d});
    }
    long long total_lost = 0;
    for (auto& item : groups)
    {
        vector<int> E_list;
        vector<int> N_list;
        for (const auto& drone : item.second)
        {
            if (drone.second == 'E')
            {
                E_list.push_back(drone.first);
            }
            else
            {
                N_list.push_back(drone.first);
            }
        }
        sort(E_list.begin(), E_list.end());
        sort(N_list.begin(), N_list.end());
        for (int x_e : E_list)
        {
            long long limit = (long long)x_e + K;
            auto lower = lower_bound(N_list.begin(), N_list.end(), x_e);
            auto upper = lower_bound(N_list.begin(), N_list.end(), limit);
            total_lost += distance(lower, upper);
        }
    }
    return (long long)N * K - total_lost;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; 
    cin >> t;
    while (t--)
    {
        int N, K; 
        cin >> N >> K;
        vector<tuple<int, int, int, char>> L;
        for (int i = 0; i < N; i++)
        {
            int X, Y, Z;
            char D;
            cin >> X >> Y >> Z >> D;
            L.emplace_back(X, Y, Z, D);
        }
        cout << solve(N, K, L) << "\n";
    }
    return 0;
}

