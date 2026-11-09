#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while(T--)
    {
        int n;
        long long k;
        cin >> n >> k;
        vector<vector<int>> east(200001);
        vector<vector<int>> north(200001);

        for(int i = 0; i < n; i++)
        {
            int x, y, z;
            char d;
            cin >> x >> y >> >> z >> d;

            int sum = x + y;

            if(d == 'E')
            {
                east[sum].push_back(x);
            }
            else
            {
                north[sum].push_back(x);
            }
        }
        
        long long blocked = 0;

        for(int 1 = 0; i <= 200000; i++)
        {
            if(east[i].empty() || north[i].empty())
                continue;
            

            sort(north[i].begin(), north[i].end());
            for(int x : east[i])
            {
                auto left = upper_bound(
                    north[i].begin(),
                    north[i].end(),
                    x
                );

                auto right = upper_bound(
                    north[i].begin(),
                    north[i].end(),
                    (long long)x + k - 1
                );

                blocked += right - left;
            }
        }

        long long answer = (long long)n * k - blocked;

        cout << answer << '\n';
    }

    return 0;
}