#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int s;
    cin >> s;

    while(s--)
    {
        int n;
        long long r;
        cin >> n >> r;
        vector<long long> a(n);
        for(int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        int smoke = 2;
        int pending = 0;
        long long first = 0;
        long long second = 0;

        bool possible = true;

        for(int i = 0; i < n; i++)
        {
            while(pending > 0 && first <= a[i])
            {
               smoke++;

            if(pending == 2)
            {
                first = second;
            }

            pending--;
            }

            if (smoke == 0)
            {
                possible = false;
                break;
            }
            smoke--;

           if (pending == 0)
           {
            first = a[i] + r;
            pending = 1;
           }
           else
           {
            second = first + r;
            pending = 2;
           }
        }


        if (possible)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }
    return 0;
}