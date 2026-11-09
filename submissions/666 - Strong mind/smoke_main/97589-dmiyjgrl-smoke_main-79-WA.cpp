
#include <iostream>
#include <queue>
using namespace std;

int main()
{
    int requests, rechargeTime;
    cin >> requests >> rechargeTime;

    int times[100];

    for(int i = 0; i < requests; i++)
    {
        cin >> times[i];
    }

    queue<int> waiting;
    int available = 2;
    bool canSmoke = true;

    for(int i = 0; i < requests; i++)
    {
        while(!waiting.empty() && waiting.front() <= times[i])
        {
            available++;
            waiting.pop();
        }

        if(available == 0)
        {
            canSmoke = false;
            break;
        }

        available--;

        int finishTime = times[i] + rechargeTime;

        if(!waiting.empty())
        {
            finishTime = max(finishTime, waiting.back() + rechargeTime);
        }

        waiting.push(finishTime);
    }

    if(canSmoke)
        cout << "YES";
    else
        cout << "NO";

    return 0;
}
